package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class JumpAlienCommand extends Command{
	
	private GameWorld g;
	
	public JumpAlienCommand(GameWorld gw){
		super("MoveToAlien");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.jumpToAlien();
	}

}
