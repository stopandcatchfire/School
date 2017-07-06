package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.Dialog;
import com.codename1.ui.events.ActionEvent;

public class HelpCommand extends Command{

	public HelpCommand(){
		super("Help");
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		Dialog.show("Help", "Controls:\n e: Expand the door\n c: Contract the door\n s: Open the door and update score\n r: Move spaceship right\n"
				+ "l: Move spaceship left\n u: Move the spaceship up\n d: Move the spaceship down\n o: Move spaceship to astronaut location"
				+ "\n a: Move the spaceship to an alien location\n w: Create new alien\n f: Initiates an alien-astronaut fight\n"
				+ " t: Tick the clock\n x: Exit game\n", "Ok", null);
	}
}
