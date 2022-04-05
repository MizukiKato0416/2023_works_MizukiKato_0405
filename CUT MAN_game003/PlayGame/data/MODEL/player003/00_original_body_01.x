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
 108;
 -8.19104;24.21863;-4.90017;,
 -3.07500;25.06310;-6.08749;,
 -3.07500;18.93954;-6.76149;,
 -8.19104;18.93954;-5.57416;,
 3.07500;25.06310;-6.08749;,
 3.07500;18.93954;-6.76149;,
 8.82196;23.97986;-4.04059;,
 8.82196;18.93954;-4.71458;,
 -3.07500;11.28205;-5.86682;,
 -6.63121;11.28205;-4.92114;,
 3.07500;11.28205;-5.86682;,
 7.42905;11.28205;-3.81860;,
 -3.21619;6.05539;-6.32952;,
 -7.40694;6.05539;-5.38384;,
 3.21615;6.05539;-6.32952;,
 8.06770;6.05539;-4.71326;,
 8.82196;23.97986;-4.04059;,
 9.22500;27.87727;-1.71465;,
 9.22500;19.67659;-2.39667;,
 8.82196;18.93954;-4.71458;,
 9.22500;28.74607;1.06691;,
 9.22500;20.69388;1.06691;,
 7.76871;28.23114;2.63956;,
 7.76871;20.69388;3.53481;,
 7.83210;11.28205;-2.39667;,
 7.42905;11.28205;-3.81860;,
 7.83210;11.28205;1.06691;,
 6.37580;11.28205;2.83173;,
 8.48924;6.05539;-2.39667;,
 8.06770;6.05539;-4.71326;,
 8.48924;6.05539;1.06691;,
 6.96609;6.05539;3.53481;,
 7.76871;28.23114;2.63956;,
 3.07500;29.07561;4.04899;,
 3.07500;20.69388;4.94424;,
 7.76871;20.69388;3.53481;,
 -3.07500;29.07561;4.04899;,
 -3.07500;20.69388;4.94424;,
 -7.97920;28.23114;3.08672;,
 -7.97920;20.69388;3.98197;,
 3.07500;11.28205;4.24264;,
 6.37580;11.28205;2.83173;,
 -3.07500;11.28205;4.24264;,
 -6.41937;11.28205;3.28037;,
 3.21615;6.05539;5.16425;,
 6.96609;6.05539;3.53481;,
 -3.21619;6.05539;5.16425;,
 -7.18538;6.05539;3.98197;,
 -7.97920;28.23114;3.08672;,
 -9.22500;28.74607;1.06691;,
 -9.22500;20.69388;1.06691;,
 -7.97920;20.69388;3.98197;,
 -9.22500;27.87727;-1.71465;,
 -9.22500;19.67659;-2.39667;,
 -8.19104;24.21863;-4.90017;,
 -8.19104;18.93954;-5.57416;,
 -7.66517;11.28205;1.06691;,
 -6.41937;11.28205;3.28037;,
 -7.66517;11.28205;-2.39667;,
 -6.63121;11.28205;-4.92114;,
 -8.48837;6.05539;1.06691;,
 -7.18538;6.05539;3.98197;,
 -8.48837;6.05539;-2.39667;,
 -7.40694;6.05539;-5.38384;,
 -3.07500;29.07561;4.04899;,
 -1.66502;29.84218;2.80605;,
 -9.22500;28.74607;1.06691;,
 3.07500;29.07561;4.04899;,
 1.66502;29.84218;2.80605;,
 9.22500;28.74607;1.06691;,
 -1.66502;29.59054;-1.63238;,
 -9.22500;27.87727;-1.71465;,
 9.22500;27.87727;-1.71465;,
 1.66502;29.59054;-1.63238;,
 -3.07500;25.06310;-6.08749;,
 -8.19104;24.21863;-4.90017;,
 3.07500;25.06310;-6.08749;,
 8.82196;23.97986;-4.04059;,
 1.66502;32.11609;2.36015;,
 -1.66502;32.11609;2.36015;,
 1.66502;32.11609;-1.63238;,
 -1.66502;32.11609;-1.63238;,
 -7.18538;3.14778;3.55185;,
 -1.83967;0.51580;4.16985;,
 -3.21619;6.05539;5.16425;,
 -8.48837;3.14778;1.06691;,
 -8.48837;6.05539;1.06691;,
 -1.83967;-0.44325;1.06691;,
 1.83967;0.51580;4.16985;,
 3.21615;6.05539;5.16425;,
 1.83967;-0.44325;1.06691;,
 6.96609;3.14778;3.10469;,
 8.48924;3.14778;1.06691;,
 8.48924;6.05539;1.06691;,
 -8.48837;3.14778;-2.39667;,
 -8.48837;6.05539;-2.39667;,
 -1.83967;-0.44325;-2.39667;,
 1.83967;-0.44325;-2.39667;,
 8.48924;3.14778;-2.39667;,
 8.48924;6.05539;-2.39667;,
 -1.83967;0.51580;-5.24510;,
 -7.40694;3.14778;-4.26126;,
 -7.40694;6.05539;-5.38384;,
 -3.21619;6.05539;-6.32952;,
 1.83967;0.51580;-5.24510;,
 3.21615;6.05539;-6.32952;,
 8.06770;3.14778;-3.84082;,
 8.06770;6.05539;-4.71326;;
 
 70;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;68,69,72,73;,
 4;71,70,74,75;,
 4;70,73,76,74;,
 4;73,72,77,76;,
 4;78,79,65,68;,
 4;80,78,68,73;,
 4;81,80,73,70;,
 4;79,81,70,65;,
 4;79,78,80,81;,
 4;82,83,84,61;,
 4;85,82,61,86;,
 4;85,87,83,82;,
 4;83,88,89,84;,
 4;87,90,88,83;,
 4;91,92,93,31;,
 4;88,91,31,89;,
 4;90,92,91,88;,
 4;94,85,86,95;,
 4;94,96,87,85;,
 4;96,97,90,87;,
 4;92,98,99,93;,
 4;97,98,92,90;,
 4;100,101,102,103;,
 4;101,94,95,102;,
 4;101,100,96,94;,
 4;104,100,103,105;,
 4;100,104,97,96;,
 4;106,104,105,107;,
 4;98,106,107,99;,
 4;104,106,98,97;;
 
 MeshMaterialList {
  1;
  70;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  -0.539704;0.311601;-0.782064;,
  -0.118814;0.418849;-0.900249;,
  0.161990;0.402085;-0.901159;,
  -0.672231;-0.047951;-0.738787;,
  -0.119833;-0.003039;-0.992789;,
  0.184367;-0.007715;-0.982827;,
  -0.666087;-0.015360;-0.745716;,
  -0.120866;-0.010851;-0.992610;,
  0.191413;-0.005253;-0.981495;,
  -0.654391;-0.029890;-0.755566;,
  -0.123407;-0.077138;-0.989354;,
  0.174788;-0.057998;-0.982896;,
  0.620041;0.282589;-0.731910;,
  0.995480;0.010121;-0.094427;,
  0.949115;0.015969;0.314525;,
  0.765864;-0.053581;-0.640767;,
  0.992627;-0.080254;-0.090838;,
  0.947368;-0.070581;0.312268;,
  0.764938;-0.011712;-0.643997;,
  0.994705;-0.020009;-0.100802;,
  0.951208;-0.009277;0.308410;,
  0.752970;-0.003716;-0.658045;,
  0.991680;0.058710;-0.114563;,
  0.952360;0.059037;0.299206;,
  0.521829;0.398837;0.754072;,
  0.153864;0.557014;0.816126;,
  -0.073547;0.392475;0.916817;,
  0.592636;-0.025617;0.805063;,
  0.161313;0.012205;0.986828;,
  -0.109629;0.013551;0.993880;,
  0.617632;0.019039;0.786237;,
  0.187272;0.045273;0.981264;,
  -0.129847;0.046369;0.990449;,
  0.626244;0.020771;0.779351;,
  0.193175;-0.006230;0.981144;,
  -0.135559;-0.003823;0.990762;,
  -0.602672;0.073821;0.794567;,
  -0.971476;0.012035;0.236834;,
  -0.985943;0.017405;-0.166175;,
  -0.613341;-0.033220;0.789120;,
  -0.968085;-0.080993;0.237174;,
  -0.983588;-0.085431;-0.158923;,
  -0.631513;0.023541;0.775008;,
  -0.971997;-0.004084;0.234959;,
  -0.985708;-0.014481;-0.167838;,
  -0.639160;0.034427;0.768303;,
  -0.971060;0.075208;0.226686;,
  -0.977868;0.063480;-0.199358;,
  -0.136833;0.959599;0.245860;,
  0.146492;0.954189;0.260891;,
  -0.109781;0.660920;-0.742383;,
  0.125333;0.644626;-0.754154;,
  0.000000;0.192429;0.981311;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -0.620871;-0.470678;-0.626883;,
  -0.202074;-0.661900;-0.721841;,
  0.156755;-0.231860;-0.960036;,
  0.696586;-0.466089;-0.545462;,
  0.993189;-0.013525;-0.115727;,
  0.817224;-0.517482;0.253689;,
  0.623306;-0.401493;0.671038;,
  0.312018;-0.455362;0.833841;,
  -0.209932;-0.643208;0.736350;,
  -0.634879;-0.421365;0.647596;,
  -0.831185;-0.517871;0.202339;,
  -0.899020;-0.347953;-0.265880;,
  -0.242228;-0.959686;0.142580;,
  0.245476;-0.957017;0.154467;,
  -0.242256;-0.957764;-0.154921;,
  0.240655;-0.960676;-0.138518;,
  -0.218611;0.910809;0.350194;,
  -0.201996;0.975176;0.090712;,
  0.217099;0.969642;0.112525;,
  -0.203684;0.856448;-0.474351;,
  0.234977;0.833997;-0.499234;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.955406;0.295294;,
  -0.475224;-0.879865;0.000000;,
  0.465462;-0.878523;-0.107433;,
  0.231639;-0.933413;-0.274012;;
  70;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,18,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,18,21,11;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,24,27,17;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;17,27,30,20;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,30,33,23;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,36,39,29;,
  4;27,28,31,30;,
  4;28,29,32,31;,
  4;29,39,42,32;,
  4;30,31,34,33;,
  4;31,32,35,34;,
  4;32,42,45,35;,
  4;36,37,40,39;,
  4;37,38,41,40;,
  4;38,0,3,41;,
  4;39,40,43,42;,
  4;40,41,44,43;,
  4;41,3,6,44;,
  4;42,43,46,45;,
  4;43,44,47,46;,
  4;44,6,9,47;,
  4;71,71,48,72;,
  4;26,25,49,48;,
  4;25,24,73,49;,
  4;72,48,50,74;,
  4;49,73,75,51;,
  4;74,50,1,0;,
  4;50,51,2,1;,
  4;51,75,12,2;,
  4;52,52,52,52;,
  4;54,54,54,54;,
  4;53,53,51,50;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;64,63,35,45;,
  4;65,64,45,46;,
  4;65,67,63,64;,
  4;63,62,34,35;,
  4;67,68,78,63;,
  4;61,60,23,33;,
  4;62,61,33,34;,
  4;68,60,61,62;,
  4;66,65,46,47;,
  4;79,69,67,65;,
  4;69,70,68,67;,
  4;60,59,22,23;,
  4;70,80,60,68;,
  4;56,55,9,10;,
  4;55,66,47,9;,
  4;55,56,69,66;,
  4;57,56,10,11;,
  4;56,81,70,69;,
  4;58,57,11,21;,
  4;59,58,21,22;,
  4;81,58,80,70;;
 }
 MeshTextureCoords {
  108;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.666670;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.666670;0.333330;,
  0.333330;0.333330;,
  0.666670;0.666670;,
  0.333330;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;1.000000;,
  0.000000;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;1.000000;,
  1.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  1.000000;0.333330;,
  0.333330;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;;
 }
}
