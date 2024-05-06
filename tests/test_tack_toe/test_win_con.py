from tic_tack_toe.tic_tac_toe import Board

x_wins = [
    # Row 1 Win
    [["x", "x", "x"], 
     [" ", " ", " "], 
     [" ", " ", " "]],
    
    # Row 2 Win
    [[" ", " ", " "], 
     ["x", "x", "x"], 
     [" ", " ", " "]],
    
    # Row 3 Win
    [[" ", " ", " "], 
     [" ", " ", " "], 
     ["x", "x", "x"]],
    
    # Column 1 Win
    [["x", " ", " "], 
     ["x", " ", " "], 
     ["x", " ", " "]],
    
    # Column 2 Win
    [[" ", "x", " "], 
     [" ", "x", " "], 
     [" ", "x", " "]],
    
    # Column 3 Win
    [[" ", " ", "x"], 
     [" ", " ", "x"], 
     [" ", " ", "x"]],
    
    # Major Diagonal Win
    [["x", " ", " "], 
     [" ", "x", " "], 
     [" ", " ", "x"]],
    
    # Minor Diagonal Win
    [[" ", " ", "x"], 
     [" ", "x", " "], 
     ["x", " ", " "]]
]

o_wins = [
    # Row 1 Win
    [["o", "o", "o"], 
     [" ", " ", " "], 
     [" ", " ", " "]],
    
    # Row 2 Win
    [[" ", " ", " "], 
     ["o", "o", "o"], 
     [" ", " ", " "]],
    
    # Row 3 Win
    [[" ", " ", " "], 
     [" ", " ", " "], 
     ["o", "o", "o"]],
    
    # Column 1 Win
    [["o", " ", " "], 
     ["o", " ", " "], 
     ["o", " ", " "]],
    
    # Column 2 Win
    [[" ", "o", " "], 
     [" ", "o", " "], 
     [" ", "o", " "]],
    
    # Column 3 Win
    [[" ", " ", "o"], 
     [" ", " ", "o"], 
     [" ", " ", "o"]],
    
    # Major Diagonal Win
    [["o", " ", " "], 
     [" ", "o", " "], 
     [" ", " ", "o"]],
    
    # Minor Diagonal Win
    [[" ", " ", "o"], 
     [" ", "o", " "], 
     ["o", " ", " "]]
]

draw_boards = [
    # Draw Board 1
    [["x", "o", "x"], 
     ["o", "x", "o"], 
     ["o", "x", "o"]],
    
    # Draw Board 2
    [["o", "x", "o"], 
     ["x", "o", "x"], 
     ["x", "o", "x"]],
    
    # Draw Board 3
    [["x", "x", "o"], 
     ["o", "o", "x"], 
     ["x", "o", "x"]],
    
    # Draw Board 4
    [["o", "o", "x"], 
     ["x", "x", "o"], 
     ["o", "x", "o"]],
    
    # Draw Board 5
    [["x", "o", "x"], 
     ["x", "o", "o"], 
     ["o", "x", "x"]],
    
    # Draw Board 6
    [["o", "x", "o"], 
     ["x", "x", "o"], 
     ["o", "o", "x"]],
]

def game_state(test_board):
    board = Board(test_board)
    return board.game_state()

def test_x_wins():
    for board in x_wins:
        assert game_state(board) == "x"

def test_o_wins():
    for board in o_wins:
        assert game_state(board) == "o"

def test_draws():
    for board in draw_boards:
        assert game_state(board) == "draw"