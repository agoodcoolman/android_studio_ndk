package com.jin.android.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.jin.jni.JniLoad;

/**
 *
 */
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView = (TextView) findViewById(R.id.text);
        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String s = JniLoad.what() + "";
                s = JniLoad.setde(2);
                Toast.makeText(MainActivity.this, s, Toast.LENGTH_SHORT).show();
                // 听说下雨天,跟冲突更配哦~~
				// 测试冲突的数据在这里.哈哈哈

                // 我知道这样不好.也知道你的爱只能那么少.
                //任性
				
				// 我又要冲突

                
				
				// 说好的.
                // 提交
				// 自己租的
            }
        });
    }


}
