import tic_tack_toe.tic_tac_toe as ttt

def test_minimax():
    board = ttt.Board([[" " for i in range(3)] for i in range(3)])
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
