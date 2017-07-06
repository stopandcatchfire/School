package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class ExpandCommand extends Command{
	private GameWorld g;
	
	public ExpandCommand(GameWorld gw) {
		super("Expand");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.expand();
	}
}
