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
 104;
 1.04694;-0.90348;-2.91074;,
 1.22835;-1.40898;-3.24213;,
 0.60431;-1.32184;-4.07720;,
 0.60431;-0.59837;-2.92953;,
 -0.33315;-1.32184;-4.07720;,
 -0.33315;-0.59837;-2.92953;,
 -1.11859;-1.40898;-3.26910;,
 -0.93211;-0.87978;-2.93769;,
 1.22835;-1.94137;-4.27725;,
 0.60431;-1.94137;-6.02859;,
 -0.33315;-1.94137;-6.02859;,
 -1.11859;-1.94137;-4.30422;,
 1.22835;-2.47156;-4.26052;,
 0.60431;-2.47156;-6.01184;,
 -0.33315;-2.47156;-6.01184;,
 -1.11859;-2.47156;-4.28747;,
 -0.93211;-0.87978;-2.93769;,
 -1.11859;-1.40898;-3.26910;,
 -1.27060;-1.04341;-2.02648;,
 -1.03303;-0.60164;-2.02648;,
 -1.30611;-0.92067;-1.03318;,
 -1.08899;-0.24742;-1.03318;,
 -1.11725;-0.92067;0.34985;,
 -0.94355;-0.24742;0.19985;,
 -1.11859;-1.94137;-4.30422;,
 -1.27060;-1.94100;-2.02648;,
 -1.30611;-1.94100;-1.03318;,
 -1.11725;-1.94100;0.34985;,
 -1.11859;-2.47156;-4.28747;,
 -1.27060;-2.35887;-2.02985;,
 -1.30611;-2.35887;-1.03318;,
 -1.11725;-2.47156;0.34985;,
 -0.94355;-0.24742;0.19985;,
 -1.11725;-0.92067;0.34985;,
 -0.33315;-0.92067;1.08640;,
 -0.33315;-0.14522;0.94919;,
 0.60431;-0.92067;1.08640;,
 0.60431;-0.14522;0.94919;,
 1.23516;-0.92067;0.48170;,
 1.08199;-0.23462;0.33170;,
 -1.11725;-1.94100;0.34985;,
 -0.33315;-1.94100;1.08640;,
 0.60431;-1.94100;1.08640;,
 1.14015;-1.94100;0.48170;,
 -1.11725;-2.47156;0.34985;,
 -0.33315;-2.47156;1.08640;,
 0.60431;-2.47156;1.08640;,
 1.14015;-2.47156;0.48170;,
 1.08199;-0.23462;0.33170;,
 1.23516;-0.92067;0.48170;,
 1.49235;-0.92067;-1.03318;,
 1.35825;-0.36235;-1.03318;,
 1.45684;-1.04341;-2.02648;,
 1.27543;-0.66538;-2.02648;,
 1.22835;-1.40898;-3.24213;,
 1.04694;-0.90348;-2.91074;,
 1.14015;-1.94100;0.48170;,
 1.40864;-1.94100;-1.03318;,
 1.37313;-1.94100;-2.02648;,
 1.22835;-1.94137;-4.27725;,
 1.14015;-2.47156;0.48170;,
 1.40864;-2.35887;-1.03318;,
 1.37313;-2.35887;-2.02985;,
 1.22835;-2.47156;-4.26052;,
 1.35825;-0.36235;-1.03318;,
 0.61614;-0.14522;-1.03318;,
 0.60431;-0.14522;0.94919;,
 -0.34499;-0.14522;-1.03318;,
 -0.33315;-0.14522;0.94919;,
 -1.08899;-0.24742;-1.03318;,
 1.27543;-0.66538;-2.02648;,
 0.60431;-0.27009;-2.02648;,
 -0.33315;-0.27009;-2.02648;,
 -1.03303;-0.60164;-2.02648;,
 1.04694;-0.90348;-2.91074;,
 0.60431;-0.59837;-2.92953;,
 -0.33315;-0.59837;-2.92953;,
 -0.93211;-0.87978;-2.93769;,
 1.40864;-2.35887;-1.03318;,
 0.60431;-2.47156;1.08640;,
 0.61614;-2.35887;-1.03318;,
 -0.33315;-2.47156;1.08640;,
 -0.34499;-2.35887;-1.03318;,
 -1.30611;-2.35887;-1.03318;,
 1.37313;-2.35887;-2.02985;,
 0.60431;-2.35887;-2.02985;,
 -0.33315;-2.35887;-2.02985;,
 -1.27060;-2.35887;-2.02985;,
 1.22835;-2.47156;-4.26052;,
 0.60431;-2.47156;-6.01184;,
 -0.33315;-2.47156;-6.01184;,
 -1.11859;-2.47156;-4.28747;,
 -0.00244;0.70807;-0.28854;,
 -0.71477;-0.00426;-0.28854;,
 -0.00244;-0.00426;0.42378;,
 -0.00244;0.70807;-0.28854;,
 0.70989;-0.00426;-0.28854;,
 -0.00244;0.70807;-0.28854;,
 -0.00244;-0.00426;-1.00087;,
 -0.00244;-0.00426;-1.00087;,
 -0.00244;-0.71658;-0.28854;,
 -0.00244;-0.71658;-0.28854;,
 -0.00244;-0.71658;-0.28854;,
 -0.00244;-0.71658;-0.28854;;
 
 63;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;17,24,25,18;,
 4;18,25,26,20;,
 4;20,26,27,22;,
 4;24,28,29,25;,
 4;25,29,30,26;,
 4;26,30,31,27;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;33,40,41,34;,
 4;34,41,42,36;,
 4;36,42,43,38;,
 4;40,44,45,41;,
 4;41,45,46,42;,
 4;42,46,47,43;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;49,56,57,50;,
 4;50,57,58,52;,
 4;52,58,59,54;,
 4;56,60,61,57;,
 4;57,61,62,58;,
 4;58,62,63,59;,
 4;48,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,23;,
 4;64,70,71,65;,
 4;65,71,72,67;,
 4;67,72,73,69;,
 4;70,74,75,71;,
 4;71,75,76,72;,
 4;72,76,77,73;,
 4;78,60,79,80;,
 4;80,79,81,82;,
 4;82,81,31,83;,
 4;84,78,80,85;,
 4;85,80,82,86;,
 4;86,82,83,87;,
 4;88,84,85,89;,
 4;89,85,86,90;,
 4;90,86,87,91;,
 3;92,93,94;,
 3;95,94,96;,
 3;97,96,98;,
 3;99,100,93;,
 3;93,101,94;,
 3;94,102,96;,
 3;96,103,98;,
 3;92,99,93;,
 3;98,95,93;;
 
 MeshMaterialList {
  7;
  63;
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
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.561600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  0.667727;0.642977;-0.375128;,
  0.296339;0.849066;-0.437345;,
  -0.234780;0.864367;-0.444688;,
  0.814018;0.487139;-0.316339;,
  0.328409;0.843103;-0.425822;,
  -0.268636;0.855635;-0.442407;,
  0.956048;0.195804;-0.218251;,
  0.329531;0.888435;-0.319518;,
  -0.273464;0.904630;-0.326897;,
  0.979373;-0.005735;-0.201979;,
  0.941933;-0.010597;-0.335633;,
  0.000000;-0.031577;-0.999501;,
  -0.612889;0.696039;-0.374027;,
  -0.659647;0.711154;-0.243158;,
  -0.795020;0.600242;-0.087481;,
  -0.778856;0.538929;-0.320842;,
  -0.964237;0.233095;-0.126147;,
  -0.984526;0.173564;0.024160;,
  -0.941263;0.229712;-0.247498;,
  -0.998184;0.015943;-0.058090;,
  -0.998750;0.000036;0.049985;,
  -0.969592;-0.007057;-0.244625;,
  -0.998686;-0.000324;-0.051256;,
  -0.998749;0.000072;0.050000;,
  -0.873947;0.270062;0.404084;,
  -0.394238;0.218693;0.892609;,
  0.403315;0.211711;0.890234;,
  -0.889797;0.137357;0.435195;,
  -0.383527;0.109279;0.917042;,
  0.400106;0.097356;0.911283;,
  -0.888749;0.000000;0.458394;,
  -0.368197;0.000000;0.929748;,
  0.400957;-0.008788;0.916055;,
  0.410361;0.000000;0.911923;,
  0.877228;0.234126;0.419114;,
  0.838685;0.541372;-0.059362;,
  0.708764;0.657080;-0.256708;,
  0.893651;0.087846;0.440080;,
  0.993558;0.102487;0.048355;,
  0.971577;0.183995;-0.148946;,
  0.895749;-0.030811;0.443491;,
  0.996590;-0.043546;0.070094;,
  0.998004;-0.017945;-0.060554;,
  0.900336;0.000000;0.435195;,
  0.997560;0.000072;0.069813;,
  0.998747;-0.000309;-0.050053;,
  0.157755;0.983438;-0.089229;,
  -0.107647;0.990323;-0.087593;,
  0.232827;0.937559;-0.258409;,
  -0.173057;0.950849;-0.256783;,
  -0.007531;-0.999544;-0.029235;,
  0.006265;-0.999527;-0.030110;,
  -0.009904;-0.999808;0.016917;,
  0.007754;-0.999828;0.016842;,
  -0.909963;-0.013094;-0.414482;,
  0.233315;0.972270;-0.015949;,
  0.117475;0.993043;-0.008031;,
  -0.075827;0.997112;0.004274;,
  -0.151216;0.988464;0.008523;,
  -0.015063;-0.999377;-0.031914;,
  -0.030107;-0.997509;-0.063789;,
  -0.015055;-0.998177;-0.058448;,
  0.012524;-0.998108;-0.060194;,
  0.025046;-0.997419;-0.067285;,
  0.012531;-0.999355;-0.033664;,
  -0.019810;-0.999610;0.019688;,
  0.015510;-0.999689;0.019538;,
  -0.039604;-0.998440;0.039360;,
  -0.019806;-0.999231;0.033832;,
  0.015507;-0.999312;0.033681;,
  0.031010;-0.998755;0.039065;,
  -0.577348;0.577348;0.577356;,
  0.577350;0.577350;-0.577350;,
  0.577347;0.577348;0.577356;,
  -0.577348;-0.577356;-0.577348;,
  -0.577345;-0.577353;0.577353;,
  0.577345;-0.577353;0.577353;,
  0.577348;-0.577356;-0.577348;,
  -0.577350;0.577350;-0.577350;,
  0.577350;-0.577350;0.577350;;
  63;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,15,12;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,18,15;,
  4;6,9,10,10;,
  4;11,11,11,11;,
  4;54,54,21,18;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;14,17,27,24;,
  4;15,18,19,16;,
  4;16,19,20,17;,
  4;17,20,30,27;,
  4;18,21,22,19;,
  4;19,22,23,20;,
  4;20,23,30,30;,
  4;24,27,28,25;,
  4;25,28,29,26;,
  4;26,29,37,34;,
  4;27,30,31,28;,
  4;28,31,32,29;,
  4;29,32,40,37;,
  4;30,30,31,31;,
  4;31,31,33,32;,
  4;32,33,43,40;,
  4;34,37,38,35;,
  4;35,38,39,36;,
  4;36,39,3,0;,
  4;37,40,41,38;,
  4;38,41,42,39;,
  4;39,42,6,3;,
  4;40,43,44,41;,
  4;41,44,45,42;,
  4;42,45,9,6;,
  4;55,55,46,56;,
  4;56,46,47,57;,
  4;57,47,58,58;,
  4;35,36,48,46;,
  4;46,48,49,47;,
  4;47,49,13,14;,
  4;36,0,1,48;,
  4;48,1,2,49;,
  4;49,2,12,13;,
  4;59,60,61,50;,
  4;50,61,62,51;,
  4;51,62,63,64;,
  4;65,59,50,52;,
  4;52,50,51,53;,
  4;53,51,64,66;,
  4;67,65,52,68;,
  4;68,52,53,69;,
  4;69,53,66,70;,
  3;71,71,71;,
  3;73,73,73;,
  3;72,72,72;,
  3;74,74,74;,
  3;75,75,75;,
  3;76,76,76;,
  3;77,77,77;,
  3;78,78,78;,
  3;79,79,79;;
 }
 MeshTextureCoords {
  104;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.375000;0.000000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
