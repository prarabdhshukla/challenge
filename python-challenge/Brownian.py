import pygame
import math
import random
import numpy as np
WIDTH, HEIGHT=900,500
WHITE=(255,255,255)
BLUE=(0,0,255)
BLACK=(0,0,0)
BALL_RADIUS=5
STEP=0.02
BOX_ORIGIN=(200,100)
BOX=(500,300)
BOX_THICKNESS=3
ERROR=3
FPS=60
class Particle():
    def __init__(self,x,y):
        self.x=x
        self.y=y
        self.vel=0,0
    def draw(self,rect,WIN):
        pygame.draw.rect(WIN,BLACK,rect,width=BOX_THICKNESS)
        rand=random.uniform(0,1)
        pygame.draw.circle(WIN,BLUE,(int(self.x),int(self.y)),BALL_RADIUS)
class Brownian():
    def __init__(self,width=WIDTH,height=HEIGHT,ball_radius=BALL_RADIUS,step=STEP,box_origin=BOX_ORIGIN,box=BOX,box_thickness=BOX_THICKNESS,error=ERROR,fps=FPS):
        self.width=width
        self.height=height
        self.ball_radius=ball_radius
        self.WIN=pygame.display.set_mode((self.width, self.height))
        self.step=step
        self.box_origin=box_origin
        self.box=box
        self.box_thickness=box_thickness
        self.error=error
        self.fps=fps
    def run(self):
        pygame.init()
        pygame.display.set_caption("Brownian Motion")
        clock=pygame.time.Clock()
        run=True
        rect=pygame.Rect(self.box_origin[0],self.box_origin[1],self.box[0],self.box[1])
        particle=Particle(self.width/2, self.height/2)
        theta=random.uniform(0,2*math.pi)
        while(run):
            clock.tick(self.fps)
            for event in pygame.event.get():
                if event.type==pygame.QUIT:
                    run=False
            self.WIN.fill(WHITE)
            particle.draw(rect,self.WIN)
            pygame.display.update()
            particle.x+=self.step*math.cos(theta)*particle.x
            particle.y+=self.step*math.sin(theta)*particle.y
            if particle.x<=200:
                particle.x=200+self.ball_radius+self.error
                theta=random.uniform(0,0.5*math.pi)
            if particle.y<=100:
                particle.y=100+self.ball_radius+self.error
                theta=random.uniform(0,math.pi)
            if particle.x>=700:
                particle.x=700-self.ball_radius-self.error
                theta=random.uniform(0.5*math.pi,math.pi)
            if particle.y>=400:
                particle.y=400-self.ball_radius-self.error
                theta=random.uniform(math.pi,2*math.pi)
        pygame.quit()
