package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class FightCommand extends Command{
	private GameWorld g;
	
	public FightCommand(GameWorld gw){
		super("Fight");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.fight();
	}

}
