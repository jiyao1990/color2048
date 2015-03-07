/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.umeng.analytics.MobclickAgent;
import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.bean.SocializeEntity;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.controller.listener.SocializeListeners.SnsPostListener;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.sso.UMSsoHandler;


import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.Toast;
import com.google.android.gms.ads.*;
import com.jiyao.android.color2048.R;

public class JYGameActivity extends Cocos2dxActivity {

	UMSocialService mController;
	private InterstitialAd interstitial;
	private int adCounts = 0;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		Platform_android.mContext = this;
		super.onCreate(savedInstanceState);
		//友盟参数
		MobclickAgent.updateOnlineConfig( this );
		MobclickAgent.getConfigParams( this, "AdSwitch" );
		//友盟分享
		mController = UMServiceFactory.getUMSocialService("com.umeng.share");
		

		this.loadAdmob();

		
//		
		// 我的  
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		MobclickAgent.onResume(this);
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		MobclickAgent.onPause(this);
	}	
	
	public void exitGame() {
		this.finish();
		MobclickAgent.onKillProcess(this);
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public String getUMParams(String key)
	{
		String value = MobclickAgent.getConfigParams( this, "AdSwitch");
		return value;
	}

	
	public void showDialog(String pMessage) {
		
		AlertDialog.Builder builder = new AlertDialog.Builder(this);  
		builder.setMessage(pMessage)  
		       .setCancelable(false)  
		       .setPositiveButton("是", new DialogInterface.OnClickListener() {  
		           public void onClick(DialogInterface dialog, int id) {  
		                JYGameActivity.this.exitGame();  
		           }  
		       })  
		       .setNegativeButton("否", new DialogInterface.OnClickListener() {  
		           public void onClick(DialogInterface dialog, int id) {  
		                dialog.cancel();  
		           }  
		       });  
		builder.create(); 
	}
	
	public void shareWeibo(String imgPath, String text){
		
		// 设置分享内容
		mController.setShareContent(text);
		// 设置分享图片, 参数2为图片的url地址
		mController.setShareMedia(new UMImage(this, 
				imgPath));
		
		Runnable RunThread = new Runnable(){
			public void run(){
				mController.postShare(JYGameActivity.this,SHARE_MEDIA.SINA, 
				        new SnsPostListener() {
				                @Override
				                public void onStart() {
				                    Toast.makeText(JYGameActivity.this, "开始分享.", Toast.LENGTH_SHORT).show();
				                }
				                @Override
				                public void onComplete(SHARE_MEDIA platform, int eCode,SocializeEntity entity) {
				                     if (eCode == 200) {
				                         Toast.makeText(JYGameActivity.this, "分享成功.", Toast.LENGTH_SHORT).show();
				                     } else {
				                          String eMsg = "";
				                          if (eCode == -101){
				                              eMsg = "没有授权";
				                          }
				                          Toast.makeText(JYGameActivity.this, "分享失败[" + eCode + "] " + 
				                                             eMsg,Toast.LENGTH_SHORT).show();
				                     }
				              }
				});
			}
		};
		this.runOnUiThread(RunThread);

	}
	
	@Override 
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
	    super.onActivityResult(requestCode, resultCode, data);
	    /**使用SSO授权必须添加如下代码 */
	    UMSsoHandler ssoHandler = mController.getConfig().getSsoHandler(requestCode) ;
	    if(ssoHandler != null){
	       ssoHandler.authorizeCallBack(requestCode, resultCode, data);
	    }
	}
	
	public void saveData(String name, String value){
		SharedPreferences mySharedPreferences= getSharedPreferences("data", 
				Activity.MODE_PRIVATE); 
		SharedPreferences.Editor editor = mySharedPreferences.edit(); 
		editor.putString(name, value);
		editor.commit(); 
	}
	
	public String readData(String name){
		SharedPreferences mySharedPreferences= getSharedPreferences("data", 
				Activity.MODE_PRIVATE); 
		String value = mySharedPreferences.getString(name, "");
		return value;
	}
	
	  // Invoke displayInterstitial() when you are ready to display an interstitial.
	public void displayInterstitial() {

		Runnable RunThread = new Runnable() {
			public void run() {
				if (interstitial.isLoaded()) {
					interstitial.show();
				}
			}
		};
		this.runOnUiThread(RunThread);

	}
	
	void loadAdmob() {
		adCounts ++;
		String unitID;
	    if (adCounts % 2 == 0) {
	    	unitID = this.getString(R.string.ad_unit_id_p);
	    }else{
	    	unitID = this.getString(R.string.ad_unit_id_m);
	    }
		interstitial = new InterstitialAd(this);
		
		interstitial.setAdUnitId(unitID);
		interstitial.setAdListener(new AdListener() {

			@Override
			public void onAdClosed() {
				loadAdmob();
				super.onAdClosed();
			}

			@Override
			public void onAdFailedToLoad(int errorCode) {
				if(errorCode == AdRequest.ERROR_CODE_INTERNAL_ERROR || errorCode == AdRequest.ERROR_CODE_NETWORK_ERROR){
					loadAdmob();
				}
				super.onAdFailedToLoad(errorCode);
			}

		});

		// Create ad request.
		AdRequest adRequest = new AdRequest.Builder().build();
		// Begin loading your interstitial.
		interstitial.loadAd(adRequest);
	}
}
