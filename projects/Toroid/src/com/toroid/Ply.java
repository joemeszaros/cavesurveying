package com.toroid;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Random;

public class Ply {
	
	public float[] points;
	public float[] normals;
	public float[] colors;
	public int[] indices;
	
	public void importStream(InputStream is) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        String line;
        int vercnt = 0;
        int facecnt = 0;
        boolean normal = false;
        while ((line = br.readLine()) != null) {
            if (line.startsWith("element vertex")) {
                String[] parts = line.split(" ");
                vercnt = Integer.parseInt(parts[2]);
            }
            
            if (line.startsWith("element face")) {
                String[] parts = line.split(" ");
                facecnt = Integer.parseInt(parts[2]);
            }
            
            if (line.startsWith("property float nx")) {
                normal = true;
            }
            
            if (line.startsWith("end_header")) {
                System.out.println("break, vertices : " + vercnt + " faces : "  + facecnt);
                break;
            }
            
        }
        
        colors = new float[vercnt*4];
        
        for (int i = 0; i < vercnt; i++) {
        	colors[i*4+0] =  0.4f;
        	colors[i*4+1] = 1 - (i)/(vercnt*1.0f);
        	colors[i*4+2] = (i)/(vercnt*1.0f);
        	colors[i*4+3] = 1.0f;
        }
        
        points = new float[vercnt*3];
        normals = new float[vercnt*3];
        
        for (int i = 0; i < vercnt; i++) {
             line = br.readLine();
             String[] coords = line.split(" ");
             Float x = Float.parseFloat(coords[0]);
             Float y = Float.parseFloat(coords[1]);
             Float z = Float.parseFloat(coords[2]);
             points[i*3+0] = x;
             points[i*3+1] = y;
             points[i*3+2] = z;
             
             if (normal) {
                 line = br.readLine();
                 String[] norms = line.split(" ");
                 Float nx = Float.parseFloat(norms[0]);
                 Float ny = Float.parseFloat(norms[1]);
                 Float nz = Float.parseFloat(norms[2]);
                 normals[i*3+0] = nx;
                 normals[i*3+1] = ny;
                 normals[i*3+2] = nz;
             }
             
        }
        
        indices = new int[facecnt*3];

        for (int i = 0; i < facecnt; i++) {
            line = br.readLine();
            String[] pos = line.split(" ");
             int i1 = Integer.parseInt(pos[1]);
             int i2 = Integer.parseInt(pos[2]);
             int i3 = Integer.parseInt(pos[3]);
             indices[i*3+0] = i1;
             indices[i*3+1] = i2;
             indices[i*3+2] = i3;
        }
        
        br.close();
		
	}
}
