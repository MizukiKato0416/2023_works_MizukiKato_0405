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
 92;
 -2.42014;-0.56231;-2.74186;,
 -1.10051;-0.56231;-3.46992;,
 -1.12088;-6.38249;-3.22669;,
 -2.37631;-6.38249;-2.54434;,
 0.76288;-0.56231;-3.46992;,
 0.65186;-6.38249;-3.22669;,
 2.08269;-0.56231;-3.03178;,
 1.90745;-6.38249;-2.81606;,
 -0.92662;-12.22779;-3.10108;,
 -2.09156;-12.22779;-2.41874;,
 0.71833;-12.22779;-3.10108;,
 1.88341;-12.22779;-2.69045;,
 -0.66814;-18.07309;-3.03791;,
 -1.74372;-18.07309;-2.35556;,
 0.85065;-18.07309;-3.03791;,
 1.92637;-18.07309;-2.62728;,
 2.08269;-0.56231;-3.03178;,
 2.62628;-0.56231;-1.55360;,
 2.42459;-6.38249;-1.49344;,
 1.90745;-6.38249;-2.81606;,
 2.62628;-0.56231;0.36272;,
 2.42459;-6.38249;0.30257;,
 2.18304;-0.56231;1.62310;,
 2.00292;-6.38249;1.85628;,
 2.36328;-12.22779;-1.49344;,
 1.88341;-12.22779;-2.69045;,
 2.36328;-12.22779;0.30257;,
 1.97200;-12.22779;1.29382;,
 2.36943;-18.07309;-1.49344;,
 1.92637;-18.07309;-2.62728;,
 2.36943;-18.07309;0.30257;,
 2.00816;-18.07309;1.04530;,
 2.18304;-0.56231;1.62310;,
 0.76288;-0.56231;2.27904;,
 0.65186;-6.38249;2.47104;,
 2.00292;-6.38249;1.85628;,
 -1.10051;-0.56231;2.27904;,
 -1.12088;-6.38249;2.47104;,
 -2.48690;-0.56231;1.70908;,
 -2.43982;-6.38249;1.93686;,
 0.71833;-12.22779;1.90858;,
 1.97200;-12.22779;1.29382;,
 -0.92662;-12.22779;1.90858;,
 -2.15049;-12.22779;1.37440;,
 0.85065;-18.07309;1.66007;,
 2.00816;-18.07309;1.04530;,
 -0.66814;-18.07309;1.66007;,
 -1.79814;-18.07309;1.12589;,
 -2.48690;-0.56231;1.70908;,
 -2.96390;-0.56231;0.36272;,
 -2.89361;-6.38249;0.30257;,
 -2.43982;-6.38249;1.93686;,
 -2.96390;-0.56231;-1.55360;,
 -2.89361;-6.38249;-1.49344;,
 -2.42014;-0.56231;-2.74186;,
 -2.37631;-6.38249;-2.54434;,
 -2.57157;-12.22779;0.30257;,
 -2.15049;-12.22779;1.37440;,
 -2.57157;-12.22779;-1.49344;,
 -2.09156;-12.22779;-2.41874;,
 -2.18692;-18.07309;0.30257;,
 -1.79814;-18.07309;1.12589;,
 -2.18692;-18.07309;-1.49344;,
 -1.74372;-18.07309;-2.35556;,
 -1.10051;-0.56231;2.27904;,
 -1.10051;0.72284;0.36272;,
 -2.96390;-0.56231;0.36272;,
 0.76288;-0.56231;2.27904;,
 0.76288;0.72284;0.36272;,
 2.62628;-0.56231;0.36272;,
 -1.10051;0.72284;-1.55360;,
 -2.96390;-0.56231;-1.55360;,
 0.76288;0.72284;-1.55360;,
 2.62628;-0.56231;-1.55360;,
 -1.10051;-0.56231;-3.46992;,
 -2.42014;-0.56231;-2.74186;,
 0.76288;-0.56231;-3.46992;,
 2.08269;-0.56231;-3.03178;,
 -2.18692;-18.07309;0.30257;,
 -0.66814;-19.45563;0.30257;,
 -0.66814;-18.07309;1.66007;,
 0.85065;-19.45563;0.30257;,
 0.85065;-18.07309;1.66007;,
 2.36943;-18.07309;0.30257;,
 -2.18692;-18.07309;-1.49344;,
 -0.66814;-19.45563;-1.49344;,
 0.85065;-19.45563;-1.49344;,
 2.36943;-18.07309;-1.49344;,
 -1.74372;-18.07309;-2.35556;,
 -0.66814;-18.07309;-3.03791;,
 0.85065;-18.07309;-3.03791;,
 1.92637;-18.07309;-2.62728;;
 
 54;
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
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;;
 
 MeshMaterialList {
  1;
  54;
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
  60;
  -0.696883;0.291319;-0.655353;,
  -0.247737;-0.039167;-0.968035;,
  0.205892;0.469512;-0.858584;,
  -0.724664;-0.037273;-0.688094;,
  -0.250831;-0.035148;-0.967393;,
  0.160653;-0.032324;-0.986481;,
  -0.726544;-0.047936;-0.685446;,
  -0.262069;-0.027748;-0.964650;,
  0.168971;-0.014363;-0.985516;,
  -0.701402;-0.290567;-0.650851;,
  -0.296989;-0.426473;-0.854353;,
  0.230731;-0.428855;-0.873411;,
  0.690593;-0.046316;-0.721759;,
  0.854290;0.470833;-0.220239;,
  0.951348;0.287036;0.112017;,
  0.690026;-0.031372;-0.723105;,
  0.982675;-0.023995;-0.183777;,
  0.987658;-0.023518;0.154850;,
  0.693779;-0.009102;-0.720130;,
  0.982281;-0.004643;-0.187357;,
  0.983156;-0.008638;0.182565;,
  0.670283;-0.289364;-0.683366;,
  0.874247;-0.422911;-0.238406;,
  0.876610;-0.407435;0.256031;,
  0.707224;0.326081;0.627301;,
  0.242746;0.500946;0.830739;,
  -0.141667;0.336142;0.931095;,
  0.749658;-0.030183;0.661137;,
  0.216058;-0.032204;0.975849;,
  -0.194981;-0.034331;0.980206;,
  0.737585;-0.038008;0.674184;,
  0.225991;-0.065514;0.971924;,
  -0.204032;-0.077262;0.975911;,
  0.696130;-0.271499;0.664599;,
  0.270387;-0.412387;0.869958;,
  -0.253274;-0.420584;0.871184;,
  -0.689031;0.341585;0.639184;,
  -0.946520;0.302220;0.112969;,
  -0.849108;0.469305;-0.242424;,
  -0.734125;-0.038581;0.677918;,
  -0.987111;-0.034303;0.156314;,
  -0.973565;-0.035034;-0.225709;,
  -0.721418;-0.079517;0.687919;,
  -0.981409;-0.063537;0.181104;,
  -0.970532;-0.059120;-0.233609;,
  -0.675475;-0.308389;0.669798;,
  -0.861476;-0.441011;0.251730;,
  -0.860068;-0.437930;-0.261725;,
  -0.259317;0.932614;0.250969;,
  0.262778;0.931859;0.250175;,
  -0.267404;0.928843;-0.256408;,
  0.253708;0.933653;-0.252832;,
  -0.327401;-0.881094;0.341295;,
  0.331860;-0.879571;0.340917;,
  -0.332624;-0.887496;-0.318923;,
  0.315856;-0.895141;-0.314574;,
  -0.401656;0.832673;0.381219;,
  0.414112;0.828123;0.377788;,
  -0.220582;0.842689;-0.491141;,
  0.381284;0.838735;-0.388775;;
  54;
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
  4;36,56,48,56;,
  4;26,25,49,48;,
  4;25,24,57,49;,
  4;37,48,50,38;,
  4;48,49,51,50;,
  4;49,14,13,51;,
  4;38,50,58,0;,
  4;50,51,2,58;,
  4;51,13,59,2;,
  4;46,52,35,45;,
  4;52,53,34,35;,
  4;53,23,33,34;,
  4;47,54,52,46;,
  4;54,55,53,52;,
  4;55,22,23,53;,
  4;9,10,54,47;,
  4;10,11,55,54;,
  4;11,21,22,55;;
 }
 MeshTextureCoords {
  92;
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
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;;
 }
}
