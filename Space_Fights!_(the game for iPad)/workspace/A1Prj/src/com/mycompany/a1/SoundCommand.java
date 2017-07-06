package com.mycompany.a1;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class SoundCommand extends Command{
	private GameWorld g;
	
	public SoundCommand(GameWorld gw){
		super("Sound");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.setSound();
	}

}
