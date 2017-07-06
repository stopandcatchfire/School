package com.mycompany.a3;

public interface ICollider {
	
	public boolean checkCollisions(Opponent o);
	public void handleCollision(Opponent o);
}
