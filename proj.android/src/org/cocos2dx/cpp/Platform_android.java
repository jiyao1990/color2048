package org.cocos2dx.cpp;

import org.json.JSONException;
import org.json.JSONObject;

import org.cocos2dx.cpp.AppActivity;

public class Platform_android {
	public static AppActivity mContext;

	public static String callPlatformFunc(String functionName,String jsonContent){
		
		if(functionName.equals("openUmengShare")){
			JSONObject jsonObj;
			try {
				jsonObj = new JSONObject(jsonContent);
				String messageInfo = null;
				String imgPath = null;
				if(jsonObj.has("messageInfo")){
					messageInfo = jsonObj.getString("messageInfo");
				}
				if(jsonObj.has("imgPath")){
					imgPath = jsonObj.getString("imgPath");
				}
				
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		return "";
	}

}
