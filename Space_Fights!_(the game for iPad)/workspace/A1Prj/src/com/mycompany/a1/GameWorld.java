package com.mycompany.a1;

import java.util.Observable;
import java.util.Random;

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
	private int points = 0;
	private boolean sound = false;
	private int worldWidth;
	private int worldHeight;
	private int astronautsRescued = 0;
	private int aliensSneakedIn = 0;
	private int astronautsOutside = 0;
	private int aliensOutside = 0;
	private int time = 0;
	private Random rand = new Random();
	
	/* init instantiates all initial conditions of a GameWorld.
	 * width/height and area of screen(world) and instantiates
	 * all GameObjects.
	 */
	public void init(){
		//worldWidth = 1024;
		//worldHeight = 786;
		//worldSize = worldWidth * worldHeight;
		
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
		sc.add(a);
		sc.add(b);
		sc.add(c);
		sc.add(d);
		sc.add(z);
		sc.add(y);
		sc.add(x);
		sc.add(s);
		while(it.hasNext()){
			if((o = it.getNext()) instanceof Astronaut)
				astronautsOutside++;
			if(o instanceof Alien)
				aliensOutside++;
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
	
	public void openDoor(){
		
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
						if(shipRight > o2.getX() && shipLeft < o2.getX() && shipTop > o2.getY() && shipBottom < o2.getY()){
							if(o2 instanceof Astronaut){
								Astronaut a = (Astronaut) o2;					//Since I guarantee that p is an Astronaut in this case, I feel safe casting.
								setPoints(getPoints() + a.getHealth() + 5);
								astronautsOutside--;
								astronautsRescued++;
								it2.remove(o2);	
							}
							else if(o2 instanceof Alien){
								setPoints(getPoints() - 10);
								aliensOutside --;
								aliensSneakedIn++;
								it2.remove(o2);
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
	 * Work in process, since we aren't handling collisions yet, just spawning if 2 or more aliens.
	 * 
	 * Handling alien collisions, if collision, new alien spawns nearby.
	 * Should be called after every move() call made.
	 */
	
	public void alienCollisionCheck(){
		
		it = sc.getIterator();
		
		if(aliensOutside>0){
			
			int r = rand.nextInt(aliensOutside) + 1;
			
			while(it.hasNext()){
				if((o = it.getNext()) instanceof Alien){
					r--;
				}
				if(r == 0){
					spawnNewAlien(o.getX(), o.getY());
					break;
				}
			}
			
		}
		else{
			final float x;
			final float y;
			x = (float) rand.nextInt(1024);
			y = (float) rand.nextInt(724);
			
			spawnNewAlien(x,y);
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
	public void spawnNewAlien(float newX, float newY) {
		l = new Alien();
		l.setX(newX+5);
		l.setY(newY+5);
		sc.add(l);
		aliensOutside++;
		
		this.setChanged();
		this.notifyObservers();
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
			}
		}
		
		this.setChanged();
		this.notifyObservers();
	}
	
	/*
	 * Each time clock tick from console (t) occurs, moves all objects.  Also updates
	 * location of Spaceship to reflect any movement commands that may have come in.
	 */
	
	public void tickClock(){	
		
		time++;
		it = sc.getIterator();
		while(it.hasNext()){
			if(!((o = it.getNext()) instanceof Spaceship)){
				opp = (Opponent) o;
				opp.move();
				opp.updateLocation();
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
		if(sound == true)
			sound = false;
		else
			sound = true;
		
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
	
	//toString prints "scoreboard" of sorts to console.
	@Override
	public String toString(){
		System.out.println("Current Score: " + points + " | Time: " + time + " | Astronauts Rescued: " + astronautsRescued 
				+ " | Aliens Snuck In: " + aliensSneakedIn + " | Astronauts Outside: " + astronautsOutside 
				+ " | Aliens Outside: " + aliensOutside);
		return null;
	}
}
