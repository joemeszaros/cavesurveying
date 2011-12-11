package com.toroid;

import java.io.IOException;

import android.app.Activity;
import android.content.res.Resources;
import android.content.res.Resources.NotFoundException;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;


public class ToroidActivity extends Activity {
    View mVictimContainer;
    View mVictim1;
    View mVictim2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.surface_view_overlay);

        Resources myResources = getResources();
        
        GLSurfaceView glSurfaceView =
            (GLSurfaceView) findViewById(R.id.glsurfaceview);
        try {
			glSurfaceView.setRenderer(new MeshRenderer(false, myResources.openRawResource(R.raw.vv)));
		} catch (NotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

        // Find the views whose visibility will change
        mVictimContainer = findViewById(R.id.hidecontainer);
        mVictim1 = findViewById(R.id.hideme1);
        mVictim1.setOnClickListener(new HideMeListener(mVictim1));
        mVictim2 = findViewById(R.id.hideme2);
        mVictim2.setOnClickListener(new HideMeListener(mVictim2));

        // Find our buttons
        ImageButton visibleButton = (ImageButton) findViewById(R.id.vis);
        //Button invisibleButton = (Button) findViewById(R.id.invis);

        // Wire each button to a click listener
        visibleButton.setOnClickListener(mVisibleListener);
        //invisibleButton.setOnClickListener(mInvisibleListener);
        //goneButton.setOnClickListener(mGoneListener);
    }

    @Override
    protected void onResume() {
        // Ideally a game should implement onResume() and onPause()
        // to take appropriate action when the activity looses focus
        super.onResume();
    }

    @Override
    protected void onPause() {
        // Ideally a game should implement onResume() and onPause()
        // to take appropriate action when the activity looses focus
        super.onPause();
    }

    class HideMeListener implements OnClickListener {
        final View mTarget;

        HideMeListener(View target) {
            mTarget = target;
        }

        public void onClick(View v) {
            mTarget.setVisibility(View.INVISIBLE);
        }

    }

    OnClickListener mVisibleListener = new OnClickListener() {
        public void onClick(View v) {
            
            mVictim1.setVisibility(View.VISIBLE);
            mVictim2.setVisibility(View.VISIBLE);
            mVictimContainer.setVisibility(View.VISIBLE);
        }
    };

    OnClickListener mInvisibleListener = new OnClickListener() {
        public void onClick(View v) {
            mVictim1.setVisibility(View.INVISIBLE);
            mVictim2.setVisibility(View.INVISIBLE);
            mVictimContainer.setVisibility(View.INVISIBLE);
        }
    };

    OnClickListener mGoneListener = new OnClickListener() {
        public void onClick(View v) {
            mVictim1.setVisibility(View.GONE);
            mVictim2.setVisibility(View.GONE);
            mVictimContainer.setVisibility(View.GONE);
        }
    };
}