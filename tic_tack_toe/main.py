import sys
import os
import random
from tic_tac_toe import *
so_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
sys.path.append(so_dir)
from myVec import MyVec

def user_compete(board, ai, player):
    turn = 0
    players_turn = True if player.xo == "x" else False
    while board.game_state() == "ongoing": 
        if players_turn:    
            print(f"Turn {turn}.")
            board.draw()
            player.make_move(board)
            turn += 1
        else: 
            ai.make_move(board)    
        players_turn = not players_turn
    end_state = board.game_state()
    board.draw()
    if end_state == "draw":
        print("Draw! :/")
    elif end_state == player.xo:
        print("You Win!")
    else:
        print("You lose :(")
            
def play_game():
    print("Lets play tic-tac-toe!")
    print("Do you want to play against:")
    print("1. Random")
    print("2. Minimax")
    selected = None
    while not selected:
        selected = input("1 or 2 >>> ")
        try:
            selected = int(selected)
            if selected != 1 and selected != 2:
                selected = None
        except: 
            selected = None
    user_plays = random.choice(["x", "o"])
    ai_plays = "x" if user_plays == "o" else "o"
    print(f"You play {user_plays.upper()}'s AI plays {ai_plays.upper()}'s")
    board_array = MyVec([MyVec([" " for i in range(3)]) for i in range(3)])
    sea_board = Board(board_array)
    py_board = Board([[" " for i in range(3)] for i in range(3)])
    if selected == 1:
        user_compete(sea_board, RandomBot(ai_plays), Human(user_plays))
    else:
        user_compete(sea_board, MinimaxBot(ai_plays), Human(user_plays))

if __name__ == "__main__":
    play_game()