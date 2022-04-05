xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 112;
 -31.33486;95.08772;-31.37193;,
 31.33486;95.08772;-31.37193;,
 31.33486;-0.40504;-46.00604;,
 -31.33486;-0.40504;-46.00604;,
 31.33486;95.08772;-31.37193;,
 31.33486;166.28664;46.00604;,
 46.00604;-0.40504;46.00604;,
 31.33486;-0.40504;-46.00604;,
 31.33486;166.28664;46.00604;,
 -31.33486;166.28664;46.00604;,
 -46.00604;-0.40504;46.00604;,
 46.00604;-0.40504;46.00604;,
 -31.33486;166.28664;46.00604;,
 -31.33486;95.08772;-31.37193;,
 -31.33486;-0.40504;-46.00604;,
 -46.00604;-0.40504;46.00604;,
 31.33486;95.08772;-31.37193;,
 -31.33486;95.08772;-31.37193;,
 -29.66206;294.58582;-1.11336;,
 29.66206;294.58582;-1.11336;,
 29.66206;95.39576;-29.62181;,
 -29.66206;95.39576;-29.62181;,
 29.66206;294.58582;-1.11336;,
 29.66206;238.22083;44.26016;,
 29.66206;164.33887;44.26016;,
 29.66206;95.39576;-29.62181;,
 29.66206;238.22083;44.26016;,
 -29.66206;238.22083;44.26016;,
 -29.66206;164.33887;44.26016;,
 29.66206;164.33887;44.26016;,
 -29.66206;238.22083;44.26016;,
 -29.66206;294.58582;-1.11336;,
 -29.66206;95.39576;-29.62181;,
 -29.66206;164.33887;44.26016;,
 29.66206;294.58582;-1.11336;,
 -29.66206;294.58582;-1.11336;,
 36.39392;48.05550;-7.99542;,
 36.61830;37.33358;-7.99542;,
 33.30370;37.33358;-27.99542;,
 33.20151;48.05550;-27.99542;,
 -36.39392;48.05550;-7.99542;,
 -33.20151;48.05550;-27.99542;,
 -33.30370;37.33358;-27.99542;,
 -36.61830;37.33358;-7.99542;,
 38.60371;70.11791;30.50280;,
 39.51637;59.39600;30.50280;,
 37.92259;59.39600;10.50280;,
 37.03308;70.11791;10.50280;,
 -38.60371;70.11791;30.50280;,
 -37.03308;70.11791;10.50280;,
 -37.92259;59.39600;10.50280;,
 -39.51637;59.39600;30.50280;,
 10.43018;3.69914;46.11544;,
 30.43018;3.69914;46.11544;,
 30.43018;13.89940;46.11544;,
 10.43018;13.89940;46.11544;,
 -23.53678;23.58327;46.11544;,
 -3.53678;23.58327;46.11544;,
 -3.53678;33.78353;46.11544;,
 -23.53678;33.78353;46.11544;,
 -23.53678;23.58327;-42.42314;,
 -23.53678;33.78353;-40.85550;,
 -3.53678;33.78353;-40.85550;,
 -3.53678;23.58327;-42.42314;,
 4.55617;47.34817;46.11544;,
 24.55617;47.34817;46.11544;,
 24.55617;57.54843;46.11544;,
 4.55617;57.54843;46.11544;,
 4.55617;47.34817;-38.81767;,
 4.55617;57.54843;-37.22033;,
 24.55617;57.54843;-37.22033;,
 24.55617;47.34817;-38.81767;,
 -26.52621;72.60734;46.11544;,
 -6.52621;72.60734;46.11544;,
 -6.52621;82.80760;46.11544;,
 -26.52621;82.80760;46.11544;,
 -26.52621;72.60734;-34.84772;,
 -26.52621;82.80760;-33.34488;,
 -6.52621;82.80760;-33.34488;,
 -6.52621;72.60734;-34.84772;,
 -26.52621;155.32224;-21.09745;,
 -26.52621;165.52251;-19.59461;,
 -6.52621;165.52251;-19.59461;,
 -6.52621;155.32224;-21.09745;,
 26.52621;155.32224;-21.09745;,
 6.52621;155.32224;-21.09745;,
 6.52621;165.52251;-19.59461;,
 26.52621;165.52251;-19.59461;,
 -26.52621;192.75520;-15.80706;,
 -26.52621;202.95547;-14.30422;,
 -6.52621;202.95547;-14.30422;,
 -6.52621;192.75520;-15.80706;,
 26.52621;192.75520;-15.80706;,
 6.52621;192.75520;-15.80706;,
 6.52621;202.95547;-14.30422;,
 26.52621;202.95547;-14.30422;,
 -26.52621;223.64698;-11.39199;,
 -26.52621;233.84724;-9.88915;,
 -6.52621;233.84724;-9.88915;,
 -6.52621;223.64698;-11.39199;,
 26.52621;223.64698;-11.39199;,
 6.52621;223.64698;-11.39199;,
 6.52621;233.84724;-9.88915;,
 26.52621;233.84724;-9.88915;,
 -26.52621;261.07994;-6.10160;,
 -26.52621;271.28020;-4.59876;,
 -6.52621;271.28020;-4.59876;,
 -6.52621;261.07994;-6.10160;,
 26.52621;261.07994;-6.10160;,
 6.52621;261.07994;-6.10160;,
 6.52621;271.28020;-4.59876;,
 26.52621;271.28020;-4.59876;;
 
 29;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,23,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;;
 
 MeshMaterialList {
  3;
  29;
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.700000;0.700000;0.700000;1.000000;;
   100.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326900;0.326900;0.326900;1.000000;;
   100.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;0.949000;0.106000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   1.000000;0.949000;0.106000;;
  }
 }
 MeshNormals {
  27;
  0.000000;0.470197;-0.882562;,
  0.000000;0.151480;-0.988460;,
  0.991316;0.055827;-0.119061;,
  0.000000;0.000000;1.000000;,
  -0.991316;0.055827;-0.119061;,
  0.000000;0.735878;-0.677114;,
  0.000000;0.141678;-0.989913;,
  1.000000;0.000000;0.000000;,
  0.000000;0.332440;0.943124;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.627065;0.778967;,
  0.986914;0.015027;-0.160545;,
  -0.986914;0.015027;-0.160545;,
  0.993405;0.083487;-0.078588;,
  -0.993405;0.083487;-0.078588;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.151903;-0.988395;,
  0.000000;0.000000;1.000000;,
  0.000000;0.154712;-0.987960;,
  0.000000;0.000000;1.000000;,
  0.000000;0.145760;-0.989320;,
  0.000000;0.145760;-0.989320;,
  0.000000;0.145760;-0.989320;,
  0.000000;0.145760;-0.989320;,
  0.000000;0.145760;-0.989320;;
  29;
  4;0,0,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,0,0;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,9,9;,
  4;10,10,10,10;,
  4;8,8,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;26,26,26,26;;
 }
 MeshTextureCoords {
  112;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}