package com.jeziellago.jniteste

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    external fun getAndroidId(): String

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        hello.text = getAndroidId()
    }
}
