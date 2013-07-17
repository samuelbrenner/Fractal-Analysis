#! /usr/bin/env python
"""
 Project: Python Chess
 File name: ChessGUI_pygame.py
 Description:  Uses pygame (http://www.pygame.org/) to draw the
	chess board, as well as get user input through mouse clicks.
	The chess tile graphics were taken from Wikimedia Commons, 
	http://commons.wikimedia.org/wiki/File:Chess_tile_pd.png
	
 Copyright (C) 2009 Steve Osborne, srosborne (at) gmail.com
 http://yakinikuman.wordpress.com/
 """
 
import pygame
import os
import sys
from pygame.locals import *
from ScrollingTextBox import ScrollingTextBox
from ChessBoard import ChessBoard

class ChessGUI_pygame:
	def __init__(self,graphicStyle=1):
		os.environ['SDL_VIDEO_CENTERED'] = '1' #should center pygame window on the screen
		pygame.init()
		pygame.display.init()
		self.screen = pygame.display.set_mode((500,500))
		self.boardStart_x = 50
		self.boardStart_y = 50
		pygame.display.set_caption('Python Chess')

		self.textBox = ScrollingTextBox(self.screen,525,825,50,450)
		self.LoadImages(graphicStyle)
		#pygame.font.init() - should be already called by pygame.init()
		self.fontDefault = pygame.font.Font( None, 20 )
		
		

	def LoadImages(self,graphicStyle):
		if graphicStyle == 0:
			self.square_size = 50 #all images must be images 50 x 50 pixels
			self.white_square = pygame.image.load(os.path.join("images","white_square.png")).convert()
			self.brown_square = pygame.image.load(os.path.join("images","brown_square.png")).convert()
			self.cyan_square = pygame.image.load(os.path.join("images","cyan_square.png")).convert()
			#"convert()" is supposed to help pygame display the images faster.  It seems to mess up transparency - makes it all black!
			#And, for this chess program, the images don't need to change that fast.
		elif graphicStyle == 1:
			self.square_size = 50
			self.white_square = pygame.image.load(os.path.join("images","white_square.png")).convert()
			self.brown_square = pygame.image.load(os.path.join("images","brown_square.png")).convert()
			self.cyan_square = pygame.image.load(os.path.join("images","cyan_square.png")).convert()
			
			
	def PrintMessage(self,message):
		#prints a string to the area to the right of the board
		self.textBox.Add(message)
		self.textBox.Draw()
		
	def ConvertToScreenCoords(self,chessSquareTuple):
		#converts a (row,col) chessSquare into the pixel location of the upper-left corner of the square
		(row,col) = chessSquareTuple
		screenX = self.boardStart_x + col*self.square_size
		screenY = self.boardStart_y + row*self.square_size
		return (screenX,screenY)
		
	def ConvertToChessCoords(self,screenPositionTuple):
		#converts a screen pixel location (X,Y) into a chessSquare tuple (row,col)
		#x is horizontal, y is vertical
		#(x=0,y=0) is upper-left corner of the screen
		(X,Y) = screenPositionTuple
		row = (Y-self.boardStart_y) / self.square_size
		col = (X-self.boardStart_x) / self.square_size
		return (row,col)
		
		
	def Draw(self,board,highlightSquares=[]):
		self.screen.fill((0,0,0))
		self.textBox.Draw()
		boardSize = len(board) #board should be square.  boardSize should be always 8 for chess, but I dislike "magic numbers" :)

		#draw blank board
		current_square = 0
		for r in range(boardSize):
			for c in range(boardSize):
				(screenX,screenY) = self.ConvertToScreenCoords((r,c))
				
				if board[r][c] == 'f':
					self.screen.blit(self.brown_square,(screenX,screenY))
				if board[r][c] == 'e':
					self.screen.blit(self.white_square,(screenX,screenY))
							
		#draw row/column labels around the edge of the board
		chessboard_obj = ChessBoard(0)#need a dummy object to access some of ChessBoard's methods....
		color = (255,255,255)#white
		antialias = 1
		
		#top and bottom - display cols
		
				
		#highlight squares if specified
		
		
		#draw pieces
		
		pygame.display.flip()

	def EndGame(self,board):
		self.PrintMessage("Press any key to exit.")
		self.Draw(board) #draw board to show end game status
		pygame.event.set_blocked(MOUSEMOTION)
		while 1:
			e = pygame.event.wait()
			if e.type is KEYDOWN:
				pygame.quit()
				sys.exit(0)
			if e.type is QUIT:
				pygame.quit()
				sys.exit(0)


	def GetClickedSquare(self,mouseX,mouseY):
		#test function
		print "User clicked screen position x =",mouseX,"y =",mouseY
		(row,col) = self.ConvertToChessCoords((mouseX,mouseY))
		if col < 8 and col >= 0 and row < 8 and row >= 0:
			print "  Chess board units row =",row,"col =",col

	def TestRoutine(self):
		#test function
		pygame.event.set_blocked(MOUSEMOTION)
		while 1:
			e = pygame.event.wait()
			if e.type is QUIT:
				return
			if e.type is KEYDOWN:
				if e.key is K_ESCAPE:
					pygame.quit()
					return
			if e.type is MOUSEBUTTONDOWN:
				(mouseX,mouseY) = pygame.mouse.get_pos()
				#x is horizontal, y is vertical
				#(x=0,y=0) is upper-left corner of the screen
				self.GetClickedSquare(mouseX,mouseY)
					
			


if __name__ == "__main__":
	#try out some development / testing stuff if this file is run directly
	testBoard =             [['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'],\
				 ['e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e']]
				 
	validSquares = [(5,2),(1,1),(1,5),(7,6)]

	game = ChessGUI_pygame()
	game.Draw(testBoard,validSquares)
	game.TestRoutine()
	
