package com.mycompany.a3;

import java.util.Observable;
import java.util.Random;

import com.codename1.ui.geom.Dimension;
import com.codename1.ui.geom.Point;

/*
 * GameWorld is the primary class (creates object) of a world, instantiated when game begins.
 * Holds single vector of objects navigates them with an iterator. At that point will probably implement IMovable to 
 * make the identifier easier when iterating.  Stores all world variables.
 */

public class GameWorld extends Observable{
	
	private SpaceCollection sc;
	private IIterator it;
	private IIterator it2;
	private GameObject o;
	private GameObject o2;
	private Astronaut a;
	private Alien l;
	private Rescuer r;
	private Opponent opp;
	private Opponent opp2;
	private int points = 0;
	private boolean sound = true;
	private int worldWidth;
	private int worldHeight;
	private int astronautsRescued = 0;
	private int aliensSneakedIn = 0;
	private int astronautsOutside = 0;
	private int aliensOutside = 0;
	private int time = 0;
	private Random rand = new Random();
	private Point p;
	private int worldX;
	private int worldY;
	private Sound fs;
	private Sound sa;
	private boolean paused = false;
	
	/* init instantiates all initial conditions of a GameWorld.
	 * width/height and area of screen(world) and instantiates
	 * all GameObjects.
	 */
	public void init(int wx, int wy, int ww, int wh, Sound fightSound, Sound spawnAlien){
		setWidth(ww);
		setHeight(wh);
		setX(wx);
		setY(wy);
		fs = fightSound;
		sa = spawnAlien;
		//worldSize = worldWidth * worldHeight;
		p = new Point(worldX, worldY);
		sc = new SpaceCollection();
		it = sc.getIterator();
		it2 = sc.getIterator();
		final Astronaut a = new Astronaut();
		final Astronaut b = new Astronaut();
		final Astronaut c = new Astronaut();
		final Astronaut d = new Astronaut();
		final Alien z = new Alien();
		final Alien y = new Alien();
		final Alien x = new Alien();
		final Spaceship s = Spaceship.getSpaceship();
		//setLocation and setWorld initializes random values for initial locations and width of world respectively
		a.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		b.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		c.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		d.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		z.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		y.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		x.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		s.setLocation(rand.nextInt(getWidth()),rand.nextInt(getHeight()));
		a.setWorld(ww,wh,wx,wy);
		b.setWorld(ww,wh,wx,wy);
		c.setWorld(ww,wh,wx,wy);
		d.setWorld(ww,wh,wx,wy);
		z.setWorld(ww,wh,wx,wy);
		y.setWorld(ww,wh,wx,wy);
		x.setWorld(ww,wh,wx,wy);
		s.setWorld(ww,wh,wx,wy);
		sc.add(a);
		sc.add(b);
		sc.add(c);
		sc.add(d);
		sc.add(z);
		sc.add(y);
		sc.add(x);
		sc.add(s);
		//Taking count of elements and also randomizing locations
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Astronaut){
				astronautsOutside++;
			}
			else if(o instanceof Alien){
				aliensOutside++;
			}
		}
		
		this.setChanged();
		this.notifyObservers();
		
	}
	

	/*
	 * "Opens Door" of spaceship to let in all opponents within hitBox shape.  In this case
	 * it is a square (size x size) in size.  If the (x,y) coordinates of an opponent are contained
	 * in the square(rectangle) hitBox of the door, it lets them in and checks for type and scoring.
	 * Nested for loop checks for spaceship then checks all opponents in Vector go.
	 * UPDATE: wasn't having any luck with "contains" method of rectangle
	 */
	
	public void openDoor(Sound open){
		
		it = sc.getIterator();
		it2 = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
		
				final float shipRight = o.getX() + (float)(o.getSize()/2);
				final float shipLeft = o.getX() - (float)(o.getSize()/2);
				final float shipTop = o.getY() + (float)(o.getSize()/2);
				final float shipBottom = o.getY() - (float)(o.getSize()/2);
		
				if(sc.size() == 0){
					System.out.println("Everything is on board or dead, you are now just playing a 2D 'Flight Simulator'");
					break;
				}
		
				while(it2.hasNext()){
					//if NOT next OBJ not Spaceship
					if(!((o2 = it2.getNext()) instanceof Spaceship)){
						if(shipRight > (o2.getX()+(o2.getSize()/2)) && shipLeft < (o2.getX()-(o2.getSize()/2)) && shipTop > (o2.getY()+(o2.getSize()/2)) && shipBottom < (o2.getY()-(o2.getSize()/2))){
							if(o2 instanceof Astronaut){
								Astronaut a = (Astronaut) o2;					//Since I guarantee that p is an Astronaut in this case, I feel safe casting.
								setPoints(getPoints() + a.getHealth() + 5);
								astronautsOutside--;
								astronautsRescued++;
								it2.remove(o2);	
								if(sound)
									open.play();
							}
							else if(o2 instanceof Alien){
								setPoints(getPoints() - 10);
								aliensOutside --;
								aliensSneakedIn++;
								it2.remove(o2);
								if(sound)
									open.play();
							}
						}
					}
				}
				break;
			}
		}
		this.setChanged();
		this.notifyObservers();
	}

	
	/*
	 * Fight invoked from command line play(), just selects a random astronaut assuming
	 * there are aliens to fight.  Conditionals to reflect that.
	 */
	public void fight(){
		
		int asctr = 0;
		int alctr = 0;
		boolean flg = false;
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Astronaut){
				a = (Astronaut) o;
				asctr++;
			}
			if(o instanceof Alien){
				l = (Alien) o;
				alctr++;
			}
			if(alctr > 0 && asctr > 0) {
				flg = true;
				break;
			}
		}
		
		
		if(flg){
			fight(a);
		}
		else if(alctr>0 && asctr==0){
			System.out.println("No Astronauts left to fight...");
		}
		else if(alctr == 0 && asctr>0){
			System.out.println("No Aliens left to fight..");
		}
		else
			System.out.println("Everything is on board or dead, you are now just playing a 2D 'Flight Simulator'");
		
		this.setChanged();
		this.notifyObservers();
	}

	
	
	/*
	 * Fight is pretty straight forward, decrement health with "updateHealth" then "updateColor" to reflect
	 * lost HP
	 */
	
	public void fight(Astronaut g){
		g.updateHealth();
		g.updateColor();
		g.updateSpeed();
	}
	
	/*
	 * Will cause issue if new spawn pushes it outside of boundary, but it should still come back into main
	 * area by move().
	 */
	public Alien spawnNewAlien(int newX, int newY, Opponent oppon, Opponent spawn) {
		l = new Alien();
		l.setX(newX+55);
		l.setY(newY+55);
		sc.add(l);
		aliensOutside++;
		l.setCollided(true);
		l.setColls(oppon, spawn);
		this.setChanged();
		this.notifyObservers();
		if(sound)
			sa.play();
		return l;
	}

	/*
	 * Methods to execute commands given by player.  Others I had already done may be above.
	 */
	
	
	//Expand/Contract adjust door size accordingly
	
	public void expand(){
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				break;
			}
			
		}
		r.widenDoor();
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void contract(){
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				break;
			}
		}
		r.shrinkDoor();
		
		this.setChanged();
		this.notifyObservers();
	}
	
	
	/*
	 * jumpToAlien/Astronaut goes to random opponent and gets its location, passes point to jumpToLocation.
	 */
	
	public void jumpToAlien(){
		
		it = sc.getIterator();
		it2 = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Alien){
				l = (Alien) o;
				break;
			}
		}
		
		if(aliensOutside == 0){
			System.out.println("No Aliens to jump to...");
		}
		else{
			while(it2.hasNext()){
				if((o = it2.getNext()) instanceof Spaceship){
					r = (Rescuer) o;
					r.jumpToLocation(l.getLocation());
				}
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void jumpToAstronaut(){
		
		it = sc.getIterator();
		it2 = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Astronaut){
				a = (Astronaut) o;
				break;
			}
		}
		
		if(astronautsOutside == 0){
			System.out.println("No Astronauts to jump to...");
		}		
		else{
			while(it2.hasNext()){
				if((o = it2.getNext()) instanceof Spaceship){
					r = (Rescuer) o;
					r.jumpToLocation(a.getLocation());
				}
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	
	/*
	 * Movements coming from console get passed to Spaceship from here.
	 */
	public void moveRight(){
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				r.moveRight();
				break;
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void moveLeft(){
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				r.moveLeft();
				break;
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void moveUp(){
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				r.moveUp();
				break;
			}
			
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void moveDown(){
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Spaceship){
				r = (Rescuer) o;
				r.moveDown();
				break;
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	/*
	 * Each time clock tick from console (t) occurs, moves all objects.  Also updates
	 * location of Spaceship to reflect any movement commands that may have come in.
	 */
	
	public void tickClock(Dimension d){	
		
		time++;
		it = sc.getIterator();
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Opponent){
				opp = (Opponent) o;
				opp.move(d);
				opp.updateLocation();
			}
		}
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Opponent)
				opp2=(Opponent) o;
			it2 = sc.getIterator();
			while(it2.hasNext()){
				if((o = it2.getNext()) instanceof Opponent)
					opp = (Opponent) o;
				
				if(opp!=opp2){
					if(opp2.checkCollisions(opp)){
						System.out.println("handlingCollisions");
						opp2.handleCollision(opp, this);
					}
				}
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	/*
	 * Prints details of all objects to console.
	 */
	public void printMap(){
		
		it = sc.getIterator();
		
		while(it.hasNext()){
			o =  it.getNext();
			o.toString();
		}
	}
	
	/*
	 * Setters/Getters
	 */

	public void setSound(){
		
		sound = !sound;
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public void setPoints(int score){
		points = score;
		
		this.setChanged();
		this.notifyObservers();
	}
	
	public int getPoints(){
		return points;
	}

	public int getRescued(){
		return astronautsRescued;
	}
	
	public int getSneakedIn(){
		return aliensSneakedIn;
	}
	
	public int getAstOutside(){
		return astronautsOutside;
	}
	
	public int getAlOutside(){
		return aliensOutside;
	}
	
	public int getTime(){
		return time;
	}

	public boolean getSound(){
		return sound;
	}
	
	public void setWidth(int i){
		worldWidth = i;
	}
	
	public void setHeight(int i){
		worldHeight = i;
	}
	
	public int getHeight(){
		return worldHeight;
	}
	
	public int getWidth(){
		return worldWidth;
	}
	
	public int getX(){
		return worldX;
	}
	
	public int getY(){
		return worldY;
	}
	
	public void setX(int x){
		worldX = x;
	}
	
	public void setY(int y){
		worldY = y;
	}
	
	public void playFightSound(){
		if(sound)
			fs.play();
	}
	
	//toString prints "scoreboard" of sorts to console.
	@Override
	public String toString(){
		System.out.println("Current Score: " + points + " | Time: " + time + " | Astronauts Rescued: " + astronautsRescued 
				+ " | Aliens Snuck In: " + aliensSneakedIn + " | Astronauts Outside: " + astronautsOutside 
				+ " | Aliens Outside: " + aliensOutside);
		return null;
	}

	public void setPaused(boolean b){
		paused = b;
	}

	public boolean getPaused(){
		return paused;
	}
	
	public IIterator getIterator(boolean t) {
		it = sc.getIterator();
		return it;
	}
}
