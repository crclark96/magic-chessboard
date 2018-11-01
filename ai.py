import chess
import chess.uci

def user_move(board):
    move = input("=> ")
    board.push(move)
    return board

def ai_move(board, engine):
    board.push(engine.go(movetime=2000).bestmove)
    return board


def main():
    board = chess.Board()
    engine = chess.uci.popen_engine("stockfish-9-linux/Linux/stockfish-9-64")
    engine.uci()
    if 'w' in input("w/b:"):
        print(board)
        board = user_move(board)
    else:
        print(board)
        board = ai_move(board, engine)
    print("===============")
    print(board)

if __name__ == "__main__":
    main()

