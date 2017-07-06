package com.mycompany.a3;

import java.io.InputStream;

import com.codename1.media.Media;
import com.codename1.media.MediaManager;
import com.codename1.ui.Display;

public class BGSound implements Runnable{
	private Media m;
	private InputStream is;
	
	public BGSound(String fileName){
		try{
			is = Display.getInstance().getResourceAsStream(this.getClass(), "/"+fileName);
			m = MediaManager.createMedia(is, "audio/mp3", this);
			m.play();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	public void pause(){m.pause();}
	public void play(){m.play();}

	public void run() {
		m.setTime(0);
		m.play();
	}
}
