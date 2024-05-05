import tic_tack_toe.py_types as ttt

def test_minimax():
    board = ttt.Board()
    p1 = ttt.MinimaxBot("o")
    p2 = ttt.MinimaxBot("x")
    turn = True
    for i in range(9):
        if turn:
            p1.make_move(board)
        else:
            p2.make_move(board)
        turn = not turn
    assert board.game_state() == "draw"
