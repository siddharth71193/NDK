package com.example.root.ndkpro;


import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText input;
    private TextView output;
    private TextView output1;
    private TextView output2;
    Handler handler;


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.input = (EditText)findViewById(R.id.input);
        this.output = (TextView) findViewById(R.id.result);
        this.output1 = (TextView) findViewById(R.id.result1);
        this.output2 = (TextView) findViewById(R.id.result2);
        Button button = (Button) findViewById(R.id.getoutput);
        handler = new Handler();
        button.setOnClickListener(this);

    }


    @Override
    public void onClick(View view) {
        try {
            InputMethodManager imm = (InputMethodManager)getSystemService(INPUT_METHOD_SERVICE);
            imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
        } catch (Exception e) {
            // TODO: handle exception
        }

        String s = input.getText().toString();
        if(TextUtils.isEmpty(s)){
            return;
        }

        final int n = Integer.parseInt(s);

        handler.post(new Runnable(){
            public void run() {
                long result1 = 0;
                result1 = Operation.fibonacci(n);
                output.setText("Fibonacci: "+Long.toString(result1));
            }
        });


        handler.post(new Runnable(){
            public void run() {
                int result[] = new int[10000];
                result = Operation.factorial(n);
                String xx = "";
                for(int i = result.length-1;i >= 0;i--)
                {
                    xx = xx+ result[i];
                }
                output1.setText("Factorial: "+xx);
            }
        });


        handler.post(new Runnable(){
            public void run() {
                int result[] = new int[10000];
                result = Operation.power(n, n);
                String xxy = "";
                for(int i = result.length-1;i >= 0;i--)
                {
                    xxy = xxy+ result[i];
                }
                output2.setText("Power: "+xxy);
            }
        });

    }

}

