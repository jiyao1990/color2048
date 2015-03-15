package org.cocos2dx.cpp;

import org.json.JSONException;
import org.json.JSONObject;

import org.cocos2dx.cpp.JYGameActivity;

import android.util.Log;

public class Platform_android {
	public static JYGameActivity mContext;

	public static String callPlatformFunc(String functionName,final String jsonContent){
		
		if(functionName.equals("showAd")){
			
			mContext.displayInterstitial();
			return mContext.isShowAds;

		}else if(functionName.equals("share")){
			Log.d("share======", jsonContent);
			JSONObject jsonObj;
			try {
				jsonObj = new JSONObject(jsonContent);
				String messageInfo = null;
				String imgPath = null;
				if(jsonObj.has("imagePath")){
					imgPath = jsonObj.getString("imagePath");
				}
				if(jsonObj.has("shareText")){
					messageInfo = jsonObj.getString("shareText");
				}
				
				mContext.shareWeibo(imgPath, messageInfo);

			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}else if(functionName.equals("screenShot")){
			
		}else if(functionName.equals("saveData")){
			
			JSONObject jsonObj;
			try {
				jsonObj = new JSONObject(jsonContent);
				String name = null;
				String value = null;
				if(jsonObj.has("name")){
					name = jsonObj.getString("name");
				}
				if(jsonObj.has("value")){
					value = jsonObj.getString("value");
				}
				mContext.saveData(name, value);
				
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}else if(functionName.equals("readData")){
			
			return mContext.readData(jsonContent);
			
		}else if(functionName.equals("showDialog")){
			
			Runnable runThread = new Runnable() {
				public void run() {
					mContext.showDialog(jsonContent);
				}
			};
			mContext.runOnUiThread(runThread);		
			
		}else if(functionName.equals("geUMParams")){
			
			return mContext.getUMParams(jsonContent);
			
		}
		
		return "";
	}

}
