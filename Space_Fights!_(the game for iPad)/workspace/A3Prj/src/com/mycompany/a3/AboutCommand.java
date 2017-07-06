package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.Dialog;
import com.codename1.ui.events.ActionEvent;

public class AboutCommand extends Command {
	
	public AboutCommand(){
		super("About");
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		Dialog.show("About", "Created By: Nick Wantz  CSc 133  Version: 2.0", "Ok", null);
	}
}
