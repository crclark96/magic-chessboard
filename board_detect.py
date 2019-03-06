import chess

'''
note: make sure array is populated at correct indexes when
reading from arduino
'''

start_board = [
  1,1,1,1,1,1,1,1,  # this is the bottom row
  1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1  # this is the top row
]

end_board = [
  1,1,1,1,1,1,1,1, # represents move 'e2e3'
  1,1,1,1,0,1,1,1,
  0,0,0,0,1,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1
]

def print_board(board):
  for i in range(8)[::-1]:
    for j in range(8):
      print(board[i*8+j], end=' ')
    print()

def gen_binary_board(board):
  '''
  generates a 64 len list of binary values that represent the
  board state given a chess.Board
  '''
  pieces = board.piece_map().keys()
  bin_board = [0]*64
  for piece in pieces:
    bin_board[piece] = 1

  return bin_board


def move_detect(start, end):
  '''
  takes two arrays of board occupation
  and returns valid board state from chess.py
  '''
  diff = [end[i] - start[i] for i in range(64)]
  print_board(diff)

if __name__ == '__main__':
  move_detect(start_board, end_board)



