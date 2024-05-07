import random

class Board:
    def __init__(self, board):
        self.board = board

    def __getitem__(self, i):
        return self.board[i]

    def game_state(self):
        for i in range(3): 
            # vertical
            if self.board[0][i] == self.board[1][i] == self.board[2][i] != " ":
                return self.board[0][i]
            # horizontal
            if self.board[i][0] == self.board[i][1] == self.board[i][2] != " ":
                return self.board[i][0]
        # diagonal
        if self.board[0][0] == self.board[1][1] == self.board[2][2] != " ":
            return self.board[0][0]
        if self.board[2][0] == self.board[1][1] == self.board[0][2] != " ":
            return self.board[1][1]
        for r in self.board:
            if " " in r:
                return "ongoing"
        return "draw" 

    def draw(self):
        print("_" * 60)
        for r in self.board: 
            for c in r: 
                print(c.upper() if c != " " else "_", end=" ")
            print(end="\n\n")

    def legal_moves(self):
        legal_moves = []
        for r in range(3):
            for c in range(3):
                if self.board[r][c] == " ":
                    legal_moves.append((r, c))
        return legal_moves

class Player:
    def __init__(self, xo: str):
        self.xo = xo
    def make_move(self, board: list[list[str]]) -> list[list[str]]:
        raise NotImplementedError("Implement in derived class")

class Human(Player):
    def make_move(self, board):
        legal_moves = board.legal_moves()
        human_move = None
        print("Choose a row and column. Ex: >>> 2, 1")
        while not human_move in legal_moves:
            human_move = input(">>> ")
            try: 
                human_move = human_move.split(",")
                human_move = (int(human_move[0]), int(human_move[1]))
            except:
                human_move = None
        r, c = human_move
        board[r][c] = self.xo

class RandomBot(Player):
    def make_move(self, board):         
        r, c = random.choice(board.legal_moves())
        board[r][c] = self.xo

class MinimaxBot(Player):    
    def __init__(self, xo:str):
        self.value = {xo: 1,  "o" if xo == "x" else "x": -1, "draw": 0}
        super().__init__(xo)

    def _minimax(self, board, turn, depth):
        state = board.game_state()
        if state != "ongoing":
            return None, self.value[state] / (depth + 1)
        best_score = None
        best_move = None
        for r in range(3):
            for c in range(3):
                if board[r][c] == " ": 
                    board[r][c] = turn
                    _, score = self._minimax(board, "x" if self.xo == "o" else "o", depth + 1)
                    board[r][c] = " "
                    if best_score is None:
                        best_score = score
                        best_move = (r,c)
                    elif (turn == self.xo and score > best_score) or (turn != self.xo and score < best_score):
                        best_score = score
                        best_move = (r, c)
        return best_move, best_score
    def make_move(self, board):
        move, _ = self._minimax(board, self.xo, 0)
        r, c = move
        board[r][c] = self.xo
