package com.touchthesky.www.wxapi;

import org.cocos2dx.cpp.AppActivity;

import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelmsg.ShowMessageFromWX;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler {

	private static final int TIMELINE_SUPPORTED_VERSION = 0x21020001;

	private Button gotoBtn, regBtn, launchBtn, checkBtn;

	// IWXAPI 是第三方app和微信通信的openapi接口
	private IWXAPI api;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		api = AppActivity.getCurrentInstance().getWeChatAPI();
		api.handleIntent(getIntent(), this);

		finish();
	}

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);

		setIntent(intent);
		api.handleIntent(intent, this);
	}

	// 微信发送请求到第三方应用时，会回调到该方法
	@Override
	public void onReq(BaseReq req) {
		switch (req.getType()) {
		case ConstantsAPI.COMMAND_GETMESSAGE_FROM_WX:
			goToGetMsg();
			break;
		case ConstantsAPI.COMMAND_SHOWMESSAGE_FROM_WX:
			goToShowMsg((ShowMessageFromWX.Req) req);
			break;
		default:
			break;
		}
	}

	// 第三方应用发送到微信的请求处理后的响应结果，会回调到该方法
	@Override
	public void onResp(BaseResp resp) {
		String resultString = null;

		switch (resp.errCode) {
		case BaseResp.ErrCode.ERR_OK:
			resultString = "发送成功";
			break;
		case BaseResp.ErrCode.ERR_USER_CANCEL:
			resultString = "发送取消";
			break;
		case BaseResp.ErrCode.ERR_AUTH_DENIED:
			resultString = "发送被拒绝";
			break;
		default:
			resultString = "发送返回";
			break;
		}

		Toast.makeText(this, resultString, Toast.LENGTH_LONG).show();
	}

	private void goToGetMsg() {
		// Intent intent = new Intent(this, GetFromWXActivity.class);
		// intent.putExtras(getIntent());
		// startActivity(intent);
		// finish();
	}

	private void goToShowMsg(ShowMessageFromWX.Req showReq) {
		// WXMediaMessage wxMsg = showReq.message;
		// WXAppExtendObject obj = (WXAppExtendObject) wxMsg.mediaObject;
		//
		// StringBuffer msg = new StringBuffer(); // 组织一个待显示的消息内容
		// msg.append("description: ");
		// msg.append(wxMsg.description);
		// msg.append("\n");
		// msg.append("extInfo: ");
		// msg.append(obj.extInfo);
		// msg.append("\n");
		// msg.append("filePath: ");
		// msg.append(obj.filePath);
		//
		// Intent intent = new Intent(this, ShowFromWXActivity.class);
		// intent.putExtra(Constants.ShowMsgActivity.STitle, wxMsg.title);
		// intent.putExtra(Constants.ShowMsgActivity.SMessage, msg.toString());
		// intent.putExtra(Constants.ShowMsgActivity.BAThumbData,
		// wxMsg.thumbData);
		// startActivity(intent);
		// finish();
	}
}