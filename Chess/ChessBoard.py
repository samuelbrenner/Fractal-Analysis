#! /usr/bin/env python
"""
 Project: Python Chess
 File name: ChessBoard.py
 Description:  Board layout; contains what pieces are present
	at each square.
	
 Copyright (C) 2009 Steve Osborne, srosborne (at) gmail.com
 http://yakinikuman.wordpress.com/
 """
 
import string

def isFull(a):
	if a == 'f':
		return True
	else:
		return False
def isValid(indexIn, dimension):
		if indexIn >= 0 and indexIn < dimension:
			return True
		else:
			return False
class ChessBoard:
	def __init__(self,setupType=0):
		self.squares = [['e','e','e','e','e','e','e','e'],
						['e','e','e','e','e','e','e','e'],
						['e','e','e','e','e','e','e','e'],
						['e','e','e','f','f','f','e','e'],
						['e','e','e','e','e','e','e','e'],
						['e','e','e','e','e','e','e','e'],
						['e','e','e','e','e','e','e','e'],
						['e','e','e','e','e','e','e','e']]
						
			
	def GetState(self):
		return self.squares

	def generate(self):
		new_board = self.squares
		for x in range(len(self.squares)):
			for y in range(len(self.squares[0])):
				neighborCount = 0
				for dx in range(-1, 2):
					for dy in range(-1, 2):
						if isValid(x + dx, len(self.squares)) and isValid(y + dy, len(self.squares[0])) and dx != 0 and dy != 0 and isFull(self.squares[x + dx][y + dy]):
							neighborCount += 1
				if isFull(self.squares[x][y]):
					if neighborCount < 2 or neigborCount > 3:
						new_board[x][y] = 'e'
					else:
						new_board[x][y] = 'f'
				else:
					if neighborCount == 3:
						new_board[x][y] = 'f'
		self.squares = new_board


		
	
		

	"""def MovePiece(self,moveTuple):
		fromSquare_r = moveTuple[0][0]
		fromSquare_c = moveTuple[0][1]
		toSquare_r = moveTuple[1][0]
		toSquare_c = moveTuple[1][1]

		fromPiece = self.squares[fromSquare_r][fromSquare_c]
		toPiece = self.squares[toSquare_r][toSquare_c]

		self.squares[toSquare_r][toSquare_c] = fromPiece
		self.squares[fromSquare_r][fromSquare_c] = 'e'

		fromPiece_fullString = self.GetFullString(fromPiece)
		toPiece_fullString = self.GetFullString(toPiece)
		
		if toPiece == 'e':
			messageString = fromPiece_fullString+ " moves from "+self.ConvertToAlgebraicNotation(moveTuple[0])+\
						    " to "+self.ConvertToAlgebraicNotation(moveTuple[1])
		else:
			messageString = fromPiece_fullString+ " from "+self.ConvertToAlgebraicNotation(moveTuple[0])+\
						" captures "+toPiece_fullString+" at "+self.ConvertToAlgebraicNotation(moveTuple[1])+"!"
		
		#capitalize first character of messageString
		messageString = string.upper(messageString[0])+messageString[1:len(messageString)]
		
		return messageString"""

if __name__ == "__main__":
	
	cb = ChessBoard(0)
	board1 = cb.GetState()
	for r in range(8):
		for c in range(8):
			print board1[r][c],
		print ""
		
	print "Move piece test..."
	cb.MovePiece(((0,0),(4,4)))
	board2 = cb.GetState()
	for r in range(8):
		for c in range(8):
			print board2[r][c],
		print ""
