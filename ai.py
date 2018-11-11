import chess
import chess.uci
import sys

def user_move(board):
    print(board.legal_moves)
    move = input("=> ")
    while board.parse_san(move) not in board.legal_moves:
        print("illegal move")
        move = input("=> ")
    board.push_san(move)
    return board

def ai_move(board, engine):
    engine.position(board)
    board.push(engine.go(movetime=2000).bestmove)
    return board

def main():
    board = chess.Board()
    engine = chess.uci.popen_engine("stockfish-9-linux/Linux/stockfish-9-64")
    engine.uci()
    print(board)
    while board.legal_moves:
        board = user_move(board)
        print("===============")
        print(board)
        if not board.legal_moves:
            print("you win!")
            sys.exit()
        board = ai_move(board,engine)
        print("===============")
        print(board)
    print("you lose :(")
    sys.exit()

if __name__ == "__main__":
    main()

