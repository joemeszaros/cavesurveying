/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.toroid;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.opengles.GL10;

/**
 * A vertex shaded cube.
 */
class Mesh
{
	
	private int indicesl = 0;
    public Mesh(float vertices[],float colors[],float[] normals,int indices[])
    {
        
     

        // Buffers to be passed to gl*Pointer() functions
        // must be direct, i.e., they must be placed on the
        // native heap where the garbage collector cannot
        // move them.
        //
        // Buffers with multi-byte datatypes (e.g., short, int, float)
        // must have their byte order set to native order

        
        //FloatBuffer vbb = FloatBuffer.allocate(vertices.length*4);
        //vbb.order();
    	ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
        vbb.order(ByteOrder.nativeOrder());
        mVertexBuffer = vbb.asFloatBuffer();
        mVertexBuffer.put(vertices);
        mVertexBuffer.position(0);

    	ByteBuffer nbb = ByteBuffer.allocateDirect(normals.length*4);
        nbb.order(ByteOrder.nativeOrder());
        mNormalBuffer = nbb.asFloatBuffer();
        mNormalBuffer.put(normals);
        mNormalBuffer.position(0);
        
        
        ByteBuffer cbb = ByteBuffer.allocateDirect(colors.length*4);
        cbb.order(ByteOrder.nativeOrder());
        mColorBuffer = cbb.asFloatBuffer();
        mColorBuffer.put(colors);
        mColorBuffer.position(0);

        indicesl = indices.length;
        ByteBuffer ibb = ByteBuffer.allocateDirect(indices.length*2);
        ibb.order(ByteOrder.nativeOrder());
        mIndexBuffer = ibb.asShortBuffer();
        //mIndexBuffer.put(indices);
        
        for(int i = 0; i < indices.length; i++) {
            mIndexBuffer.put((short)indices[i]);
        }
        
        mIndexBuffer.position(0);
    }

	public void draw(GL10 gl)
    {
        gl.glFrontFace(gl.GL_CW);
		
        gl.glVertexPointer(3, gl.GL_FLOAT, 0, mVertexBuffer);
        gl.glColorPointer(4, gl.GL_FLOAT, 0, mColorBuffer);
        //gl.glNormalPointer(3, gl.GL_FLOAT, mNormalBuffer);
        gl.glDrawElements(gl.GL_TRIANGLES, indicesl, gl.GL_UNSIGNED_SHORT, mIndexBuffer);
    }

    private FloatBuffer   mVertexBuffer;
    private FloatBuffer   mColorBuffer;
    private FloatBuffer   mNormalBuffer;
    private ShortBuffer  mIndexBuffer;
}
