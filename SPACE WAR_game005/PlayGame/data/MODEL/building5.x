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
 276;
 -1.92841;113.31167;-14.86325;,
 1.92841;113.31167;-14.86325;,
 1.92841;-0.12781;-48.78564;,
 -1.92841;-0.12781;-48.78564;,
 1.92841;113.31167;-14.86325;,
 1.92841;113.31167;-3.30843;,
 1.92841;-0.12781;-21.95863;,
 1.92841;-0.12781;-48.78564;,
 1.92841;113.31167;-3.30843;,
 -1.92841;113.31167;-3.30843;,
 -1.92841;-0.12781;-21.95863;,
 1.92841;-0.12781;-21.95863;,
 -1.92841;113.31167;-3.30843;,
 -1.92841;113.31167;-14.86325;,
 -1.92841;-0.12781;-48.78564;,
 -1.92841;-0.12781;-21.95863;,
 -1.92841;113.31167;14.86325;,
 -1.92841;-0.12781;48.78564;,
 1.92841;-0.12781;48.78564;,
 1.92841;113.31167;14.86325;,
 1.92841;113.31167;14.86325;,
 1.92841;-0.12781;48.78564;,
 1.92841;-0.12781;21.95863;,
 1.92841;113.31167;3.30843;,
 1.92841;113.31167;3.30843;,
 1.92841;-0.12781;21.95863;,
 -1.92841;-0.12781;21.95863;,
 -1.92841;113.31167;3.30843;,
 -1.92841;113.31167;3.30843;,
 -1.92841;-0.12781;21.95863;,
 -1.92841;-0.12781;48.78564;,
 -1.92841;113.31167;14.86325;,
 14.86325;113.31167;-1.92841;,
 14.86325;113.31167;1.92841;,
 48.78564;-0.12781;1.92841;,
 48.78564;-0.12781;-1.92841;,
 14.86325;113.31167;1.92841;,
 3.30843;113.31167;1.92841;,
 21.95863;-0.12781;1.92841;,
 48.78564;-0.12781;1.92841;,
 3.30843;113.31167;1.92841;,
 3.30843;113.31167;-1.92841;,
 21.95863;-0.12781;-1.92841;,
 21.95863;-0.12781;1.92841;,
 3.30843;113.31167;-1.92841;,
 14.86325;113.31167;-1.92841;,
 48.78564;-0.12781;-1.92841;,
 21.95863;-0.12781;-1.92841;,
 -14.86325;113.31167;-1.92841;,
 -48.78564;-0.12781;-1.92841;,
 -48.78564;-0.12781;1.92841;,
 -14.86325;113.31167;1.92841;,
 -14.86325;113.31167;1.92841;,
 -48.78564;-0.12781;1.92841;,
 -21.95863;-0.12781;1.92841;,
 -3.30843;113.31167;1.92841;,
 -3.30843;113.31167;1.92841;,
 -21.95863;-0.12781;1.92841;,
 -21.95863;-0.12781;-1.92841;,
 -3.30843;113.31167;-1.92841;,
 -3.30843;113.31167;-1.92841;,
 -21.95863;-0.12781;-1.92841;,
 -48.78564;-0.12781;-1.92841;,
 -14.86325;113.31167;-1.92841;,
 -14.14214;64.52286;0.00000;,
 0.00000;64.52286;-14.14214;,
 0.00000;62.06089;-14.14214;,
 -14.14214;62.06089;0.00000;,
 0.00000;64.52286;-14.14214;,
 14.14214;64.52286;0.00000;,
 14.14214;62.06089;0.00000;,
 0.00000;62.06089;-14.14214;,
 14.14214;64.52286;0.00000;,
 0.00000;64.52286;14.14214;,
 0.00000;62.06089;14.14214;,
 14.14214;62.06089;0.00000;,
 0.00000;64.52286;14.14214;,
 -14.14214;64.52286;0.00000;,
 -14.14214;62.06089;0.00000;,
 0.00000;62.06089;14.14214;,
 0.00000;64.52286;-14.14214;,
 -14.14214;64.52286;0.00000;,
 -14.14214;62.06089;0.00000;,
 0.00000;62.06089;-14.14214;,
 -20.05115;29.33672;0.00000;,
 0.00000;29.33672;-20.05115;,
 0.00000;25.84608;-20.05115;,
 -20.05115;25.84608;0.00000;,
 0.00000;29.33672;-20.05115;,
 20.05115;29.33672;0.00000;,
 20.05115;25.84608;0.00000;,
 0.00000;25.84608;-20.05115;,
 20.05115;29.33672;0.00000;,
 0.00000;29.33672;20.05115;,
 0.00000;25.84608;20.05115;,
 20.05115;25.84608;0.00000;,
 0.00000;29.33672;20.05115;,
 -20.05115;29.33672;0.00000;,
 -20.05115;25.84608;0.00000;,
 0.00000;25.84608;20.05115;,
 0.00000;29.33672;-20.05115;,
 -20.05115;29.33672;0.00000;,
 -20.05115;25.84608;0.00000;,
 0.00000;25.84608;-20.05115;,
 -15.43289;118.65770;-15.43289;,
 15.43289;118.65770;-15.43289;,
 15.43289;113.27045;-15.43289;,
 -15.43289;113.27045;-15.43289;,
 15.43289;118.65770;-15.43289;,
 15.43289;118.65770;15.43289;,
 15.43289;113.27045;15.43289;,
 15.43289;113.27045;-15.43289;,
 15.43289;118.65770;15.43289;,
 -15.43289;118.65770;15.43289;,
 -15.43289;113.27045;15.43289;,
 15.43289;113.27045;15.43289;,
 -15.43289;118.65770;15.43289;,
 -15.43289;118.65770;-15.43289;,
 -15.43289;113.27045;-15.43289;,
 -15.43289;113.27045;15.43289;,
 15.43289;118.65770;-15.43289;,
 -15.43289;118.65770;-15.43289;,
 -15.43289;113.27045;-15.43289;,
 15.43289;113.27045;-15.43289;,
 -21.66403;137.22619;-21.66403;,
 21.66403;137.22619;-21.66403;,
 21.66403;131.18410;-21.66403;,
 -21.66403;131.18410;-21.66403;,
 21.66403;137.22619;-21.66403;,
 21.66403;137.22619;21.66403;,
 21.66403;131.18410;21.66403;,
 21.66403;131.18410;-21.66403;,
 21.66403;137.22619;21.66403;,
 -21.66403;137.22619;21.66403;,
 -21.66403;131.18410;21.66403;,
 21.66403;131.18410;21.66403;,
 -21.66403;137.22619;21.66403;,
 -21.66403;137.22619;-21.66403;,
 -21.66403;131.18410;-21.66403;,
 -21.66403;131.18410;21.66403;,
 21.66403;137.22619;-21.66403;,
 -21.66403;137.22619;-21.66403;,
 -21.66403;131.18410;-21.66403;,
 21.66403;131.18410;-21.66403;,
 -13.09083;135.89236;-13.09083;,
 13.09083;135.89236;-13.09083;,
 13.09083;114.33865;-13.09083;,
 -13.09083;114.33865;-13.09083;,
 13.09083;135.89236;-13.09083;,
 13.09083;135.89236;13.09083;,
 13.09083;114.33865;13.09083;,
 13.09083;114.33865;-13.09083;,
 13.09083;135.89236;13.09083;,
 -13.09083;135.89236;13.09083;,
 -13.09083;114.33865;13.09083;,
 13.09083;114.33865;13.09083;,
 -13.09083;135.89236;13.09083;,
 -13.09083;135.89236;-13.09083;,
 -13.09083;114.33865;-13.09083;,
 -13.09083;114.33865;13.09083;,
 2.69363;131.33037;-21.77234;,
 2.69363;116.52628;-15.43289;,
 -2.69363;116.52628;-15.43289;,
 -2.69363;131.33037;-21.77234;,
 2.69363;116.52628;15.43289;,
 2.69363;131.33037;21.77234;,
 -2.69363;131.33037;21.77234;,
 -2.69363;116.52628;15.43289;,
 2.69363;131.33037;21.77234;,
 2.69363;116.52628;15.43289;,
 2.69363;116.52628;-15.43289;,
 2.69363;131.33037;-21.77234;,
 -2.69363;131.33037;-21.77234;,
 -2.69363;116.52628;-15.43289;,
 -2.69363;116.52628;15.43289;,
 -2.69363;131.33037;21.77234;,
 -21.77234;131.33037;-2.69363;,
 -15.43289;116.52628;-2.69363;,
 -15.43289;116.52628;2.69363;,
 -21.77234;131.33037;2.69363;,
 15.43289;116.52628;-2.69363;,
 21.77234;131.33037;-2.69363;,
 21.77234;131.33037;2.69363;,
 15.43289;116.52628;2.69363;,
 21.77234;131.33037;-2.69363;,
 15.43289;116.52628;-2.69363;,
 -15.43289;116.52628;-2.69363;,
 -21.77234;131.33037;-2.69363;,
 -21.77234;131.33037;2.69363;,
 -15.43289;116.52628;2.69363;,
 15.43289;116.52628;2.69363;,
 21.77234;131.33037;2.69363;,
 5.02331;214.06075;-6.88081;,
 6.88081;214.06075;-5.02331;,
 20.46520;136.79671;-18.60770;,
 18.60770;136.79671;-20.46519;,
 6.88081;214.06075;-5.02331;,
 2.25363;214.06075;-0.39613;,
 9.72219;136.79671;-7.86469;,
 20.46520;136.79671;-18.60770;,
 2.25363;214.06075;-0.39613;,
 0.39613;214.06075;-2.25362;,
 7.86469;136.79671;-9.72219;,
 9.72219;136.79671;-7.86469;,
 0.39613;214.06075;-2.25362;,
 5.02331;214.06075;-6.88081;,
 18.60770;136.79671;-20.46519;,
 7.86469;136.79671;-9.72219;,
 -6.88081;214.06075;5.02331;,
 -20.46520;136.79671;18.60770;,
 -18.60770;136.79671;20.46519;,
 -5.02331;214.06075;6.88081;,
 -5.02331;214.06075;6.88081;,
 -18.60770;136.79671;20.46519;,
 -7.86469;136.79671;9.72219;,
 -0.39613;214.06075;2.25362;,
 -0.39613;214.06075;2.25362;,
 -7.86469;136.79671;9.72219;,
 -9.72219;136.79671;7.86469;,
 -2.25363;214.06075;0.39613;,
 -2.25363;214.06075;0.39613;,
 -9.72219;136.79671;7.86469;,
 -20.46520;136.79671;18.60770;,
 -6.88081;214.06075;5.02331;,
 -6.88080;214.06075;-5.02331;,
 -5.02331;214.06075;-6.88081;,
 -18.60770;136.79671;-20.46520;,
 -20.46519;136.79671;-18.60770;,
 -5.02331;214.06075;-6.88081;,
 -0.39613;214.06075;-2.25363;,
 -7.86469;136.79671;-9.72219;,
 -18.60770;136.79671;-20.46520;,
 -0.39613;214.06075;-2.25363;,
 -2.25362;214.06075;-0.39613;,
 -9.72219;136.79671;-7.86469;,
 -7.86469;136.79671;-9.72219;,
 -2.25362;214.06075;-0.39613;,
 -6.88080;214.06075;-5.02331;,
 -20.46519;136.79671;-18.60770;,
 -9.72219;136.79671;-7.86469;,
 5.02331;214.06075;6.88081;,
 18.60770;136.79671;20.46520;,
 20.46519;136.79671;18.60770;,
 6.88080;214.06075;5.02331;,
 6.88080;214.06075;5.02331;,
 20.46519;136.79671;18.60770;,
 9.72219;136.79671;7.86469;,
 2.25362;214.06075;0.39613;,
 2.25362;214.06075;0.39613;,
 9.72219;136.79671;7.86469;,
 7.86469;136.79671;9.72219;,
 0.39613;214.06075;2.25363;,
 0.39613;214.06075;2.25363;,
 7.86469;136.79671;9.72219;,
 18.60770;136.79671;20.46520;,
 5.02331;214.06075;6.88081;,
 -1.42821;178.86961;0.00000;,
 3.44804;173.99336;-6.89606;,
 -3.44804;167.09727;-6.89606;,
 -8.32430;171.97351;0.00000;,
 3.44804;173.99336;-6.89606;,
 8.32430;169.11712;0.00000;,
 1.42821;162.22102;0.00000;,
 -3.44804;167.09727;-6.89606;,
 8.32430;169.11712;0.00000;,
 3.44804;173.99336;6.89606;,
 -3.44804;167.09727;6.89606;,
 1.42821;162.22102;0.00000;,
 3.44804;173.99336;6.89606;,
 -1.42821;178.86961;0.00000;,
 -8.32430;171.97351;0.00000;,
 -3.44804;167.09727;6.89606;,
 3.44804;173.99336;-6.89606;,
 -1.42821;178.86961;0.00000;,
 -8.32430;171.97351;0.00000;,
 -3.44804;167.09727;-6.89606;;
 
 74;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
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
 4;76,69,80,81;,
 4;82,83,70,79;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;96,89,100,101;,
 4;102,103,90,99;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;116,109,120,121;,
 4;122,123,110,119;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;136,129,140,141;,
 4;142,143,130,139;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;268,261,272,273;,
 4;274,275,262,271;;
 
 MeshMaterialList {
  3;
  74;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.380000;0.380000;0.380000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;0.996000;0.024000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   1.000000;0.996000;0.024000;;
  }
 }
 MeshNormals {
  70;
  0.000000;0.286500;-0.958080;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.162229;0.986753;,
  0.000000;0.286500;0.958080;,
  0.000000;-0.162229;-0.986753;,
  -1.000000;0.000000;0.000000;,
  0.958080;0.286500;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.986753;-0.162229;0.000000;,
  -0.958080;0.286500;0.000000;,
  0.986753;-0.162229;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.393649;-0.919261;,
  0.000000;-0.393649;0.919261;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.919261;-0.393649;0.000000;,
  0.919261;-0.393649;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.686212;0.241297;-0.686214;,
  0.707107;0.000000;0.707107;,
  -0.700590;-0.135442;0.700592;,
  -0.686212;0.241297;0.686214;,
  0.707107;-0.000000;0.707107;,
  0.700590;-0.135442;-0.700592;,
  -0.707107;-0.000000;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  -0.686215;0.241297;-0.686211;,
  0.707107;0.000000;-0.707107;,
  0.700592;-0.135442;0.700590;,
  0.686215;0.241297;0.686211;,
  0.707107;0.000000;-0.707107;,
  -0.700592;-0.135442;-0.700590;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  -0.500000;0.500000;-0.707107;,
  0.500000;-0.500000;-0.707107;,
  0.500000;-0.500000;0.707107;,
  -0.500000;0.500000;0.707107;,
  0.707106;0.707107;0.000000;,
  -0.707106;-0.707107;0.000000;;
  74;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;9,9,9,9;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;11,11,11,11;,
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
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;54,54,54,54;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;62,62,62,62;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;;
 }
 MeshTextureCoords {
  276;
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
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
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
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
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
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
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
  1.000000;0.000000;;
 }
}