import chess

'''
note: make sure array is populated at correct indexes when
reading from arduino
'''

start_board = chess.Board()

end_board = [
  1,1,1,1,1,1,1,1, # this is the bottom row
  1,1,1,1,0,1,1,1, # represents move 'e2e3'
  0,0,0,0,1,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1 # this is the top row
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
  takes chess.Board as start, binary board array as end
  and returns uci string of the corresponding move
  '''
  files = 'abcdefgh'
  ranks = '12345678'
  uci = ''
  bin_start = gen_binary_board(start)
  diff = [end[i] - bin_start[i] for i in range(64)]
  piece_origin = diff.index(-1)

  uci += files[chess.square_file(piece_origin)]
  uci += ranks[chess.square_rank(piece_origin)]

  if 1 in diff:
    # no capture
    piece_dest = diff.index(1)
    uci += files[chess.square_file(piece_dest)]
    uci += ranks[chess.square_rank(piece_dest)]
  else:
    # there is a capture, making this harder
    pass # for now

  return uci


if __name__ == '__main__':
  move_detect(start_board, end_board)



