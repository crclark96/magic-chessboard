#!/usr/bin/env python
# -*- coding: utf-8 -*-

import chess
import chess.uci
import sys
import smbus
import time
import move_detect

address = 0x04
bus = smbus.SMBus(1)

def uci_to_index(s):
    '''
    translates a uci move into a board-index pair (src, dst), with 0 as
    the bottom left square of the board (from the perspective of
    white) and 63 as the top right
    '''
    cols = '12345678'
    rows = 'abcdefgh'
    indexes = [0,0]
    src = s[0:2]
    dst = s[2:4]
    if src[0] not in rows or src[1] not in cols\
        or dst[0] not in rows or src[1] not in cols:
        return 0
    indexes[0] = (int(src[1]) - 1)*8 + (ord(src[0]) - ord('a'))
    indexes[1] = (int(dst[1]) - 1)*8 + (ord(dst[0]) - ord('a'))

    return tuple(indexes)


def user_move(board):
    print(board.legal_moves)
    #move = raw_input("=> ")
    new_board = []
    for i in range(64):
      new_board.append(bus.read_byte(address))
      time.sleep(0.1)
    move = move_detect.move_detect(board, new_board)
    print("received from arduino: " + str(move))
    #while board.parse_san(move) not in board.legal_moves:
    #    print("illegal move")
    #    move = raw_input("=> ")
    board.push_uci(move)
    return board

def ai_move(board, engine):
    engine.position(board)
    move = engine.go(movetime=2000).bestmove
    print(move.uci())
    print("sending to arduino: " + str(uci_to_index(move.uci())))
    bus.write_i2c_block_data(address,0,list(uci_to_index(move.uci())))
    board.push(move)
    return board

def main():
    board = chess.Board()
    engine = chess.uci.popen_engine("stockfish-9-linux/Linux/stockfish-9-64")
    engine.uci()
    print(board.unicode().encode('utf-8'))
    while board.legal_moves:
        board = user_move(board)
        print("===============")
        print(board.unicode().encode('utf-8'))
        if not board.legal_moves:
            print("you win!")
            sys.exit()
        board = ai_move(board,engine)
        print("===============")
        print(board.unicode().encode('utf-8'))
    print("you lose :(")
    sys.exit()

if __name__ == "__main__":
    main()

