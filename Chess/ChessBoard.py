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

class ChessBoard:
	def __init__(self,setupType=0):
		self.squares = [['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e'],\
						['e','e','e','e','e','e','e','e']]
						
					
			
	def GetState(self):
		return self.squares
		
	
		
	def GetFullString(self,p):
		if 'b' in p:
			name = "black "
		else:
			name = "white "
			
		if 'P' in p:
			name = name + "pawn"
		if 'R' in p:
			name = name + "rook"
		if 'T' in p:
			name = name + "knight"
		if 'B' in p:
			name = name + "bishop"
		if 'Q' in p:
			name = name + "queen"
		if 'K' in p:
			name = name + "king"
			
		return name
	
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
