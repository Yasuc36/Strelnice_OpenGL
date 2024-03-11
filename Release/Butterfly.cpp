/**
 * \file    Butterfly.cpp : This file contains the vertices and indicies for butterfly object.
 */
#include "Butterfly.h"

std::vector<float> bf_vert =
{
0.000000f, 0.078086f, -0.146961f,
0.110824f, -0.000000f, -0.224247f,
0.000000f, 0.000000f, -0.409531f,
0.000000f, -0.070301f, 0.452319f,
0.110824f, -0.000000f, 0.518382f,
0.000000f, 0.000000f, 0.726166f,
0.000000f, 0.069821f, 0.452319f,
0.110824f, 0.045295f, 0.027739f,
0.110824f, -0.045295f, 0.027739f,
0.000000f, -0.075740f, 0.034004f,
0.501040f, -0.000000f, 0.027739f,
0.427219f, 0.045295f, -0.322914f,
0.000000f, -0.078086f, -0.146961f,
0.427219f, -0.045295f, -0.322914f,
0.707865f, 0.045295f, -0.493162f,
0.737057f, -0.000000f, -0.123207f,
1.000000f, -0.000000f, -0.565862f,
0.353372f, -0.000000f, -0.673567f,
0.707865f, -0.045295f, -0.493162f,
0.678646f, -0.000000f, -0.863117f,
0.912370f, 0.000000f, -0.777113f,
0.377206f, -0.045295f, 0.425420f,
0.377206f, 0.045295f, 0.425420f,
0.595148f, -0.045295f, 0.524913f,
0.619995f, -0.000000f, 0.165116f,
0.726260f, -0.000000f, 0.374393f,
0.260810f, -0.000000f, 0.799240f,
0.595148f, 0.045295f, 0.524913f,
0.571821f, -0.000000f, 0.863117f,
0.714903f, -0.000000f, 0.703959f,
-0.110824f, -0.000000f, -0.224247f,
-0.110824f, -0.000000f, 0.518382f,
-0.110824f, 0.045295f, 0.027739f,
0.000000f, 0.075607f, 0.034004f,
-0.110824f, -0.045295f, 0.027739f,
-0.427219f, 0.045295f, -0.322914f,
-0.501040f, -0.000000f, 0.027739f,
-0.427219f, -0.045295f, -0.322914f,
-0.707865f, 0.045295f, -0.493162f,
-1.000000f, -0.000000f, -0.565862f,
-0.737057f, -0.000000f, -0.123207f,
-0.707865f, -0.045295f, -0.493162f,
-0.353372f, -0.000000f, -0.673567f,
-0.912370f, 0.000000f, -0.777113f,
-0.678646f, -0.000000f, -0.863117f,
-0.377206f, -0.045295f, 0.425420f,
-0.377206f, 0.045295f, 0.425420f,
-0.595148f, -0.045295f, 0.524913f,
-0.726260f, -0.000000f, 0.374393f,
-0.619995f, -0.000000f, 0.165116f,
-0.595148f, 0.045295f, 0.524913f,
-0.260810f, -0.000000f, 0.799240f,
-0.714903f, -0.000000f, 0.703959f,
-0.571821f, -0.000000f, 0.863117f,



0.000000f, -0.222074f, -0.166919f,
0.125874f, -0.310765f, -0.254701f,
0.000000f, -0.310765f, -0.465148f,
0.000000f, -0.390613f, 0.513747f,
0.125874f, -0.310765f, 0.588781f,
0.000000f, -0.310765f, 0.824784f,
0.000000f, -0.231461f, 0.513747f,
0.125874f, -0.259319f, 0.031506f,
0.125874f, -0.362210f, 0.031506f,
0.000000f, -0.396790f, 0.038622f,
0.578168f, -0.151673f, 0.031506f,
0.480666f, -0.138592f, -0.366768f,
0.000000f, -0.399455f, -0.166919f,
0.522332f, -0.232672f, -0.366768f,
0.754550f, 0.170295f, -0.560136f,
0.815473f, 0.164603f, -0.139939f,
1.000000f, 0.399455f, -0.642710f,
0.424799f, -0.219591f, -0.765042f,
0.835428f, 0.106768f, -0.560136f,
0.774474f, 0.112460f, -0.980333f,
0.938471f, 0.321181f, -0.882649f,
0.470401f, -0.255655f, 0.483195f,
0.428736f, -0.161605f, 0.483195f,
0.756336f, 0.006086f, 0.596200f,
0.733323f, 0.060045f, 0.187540f,
0.807903f, 0.154974f, 0.425238f,
0.328690f, -0.262165f, 0.907782f,
0.675458f, 0.069644f, 0.596200f,
0.699500f, 0.017017f, 0.980333f,
0.799909f, 0.144799f, 0.799561f,
-0.125874f, -0.310765f, -0.254701f,
-0.125874f, -0.310765f, 0.588781f,
-0.125874f, -0.259319f, 0.031506f,
0.000000f, -0.224890f, 0.038622f,
-0.125874f, -0.362210f, 0.031506f,
-0.480666f, -0.138592f, -0.366768f,
-0.578168f, -0.151673f, 0.031506f,
-0.522332f, -0.232672f, -0.366768f,
-0.754550f, 0.170295f, -0.560136f,
-1.000000f, 0.399455f, -0.642710f,
-0.815473f, 0.164603f, -0.139939f,
-0.835428f, 0.106768f, -0.560136f,
-0.424799f, -0.219591f, -0.765042f,
-0.938471f, 0.321181f, -0.882649f,
-0.774474f, 0.112460f, -0.980333f,
-0.470401f, -0.255655f, 0.483195f,
-0.428736f, -0.161605f, 0.483195f,
-0.756336f, 0.006086f, 0.596200f,
-0.807903f, 0.154974f, 0.425238f,
-0.733323f, 0.060045f, 0.187540f,
-0.675458f, 0.069644f, 0.596200f,
-0.328690f, -0.262165f, 0.907782f,
-0.799909f, 0.144799f, 0.799561f,
-0.699500f, 0.017017f, 0.980333f,



0.000000f, 0.078086f, -0.146961f,
0.110824f, -0.000000f, -0.224247f,
0.000000f, 0.000000f, -0.409531f,
0.000000f, -0.070301f, 0.452319f,
0.110824f, -0.000000f, 0.518382f,
0.000000f, 0.000000f, 0.726166f,
0.000000f, 0.069821f, 0.452319f,
0.110824f, 0.045295f, 0.027739f,
0.110824f, -0.045295f, 0.027739f,
0.000000f, -0.075740f, 0.034004f,
0.501040f, -0.000000f, 0.027739f,
0.427219f, 0.045295f, -0.322914f,
0.000000f, -0.078086f, -0.146961f,
0.427219f, -0.045295f, -0.322914f,
0.707865f, 0.045295f, -0.493162f,
0.737057f, -0.000000f, -0.123207f,
1.000000f, -0.000000f, -0.565862f,
0.353372f, -0.000000f, -0.673567f,
0.707865f, -0.045295f, -0.493162f,
0.678646f, -0.000000f, -0.863117f,
0.912370f, 0.000000f, -0.777113f,
0.377206f, -0.045295f, 0.425420f,
0.377206f, 0.045295f, 0.425420f,
0.595148f, -0.045295f, 0.524913f,
0.619995f, -0.000000f, 0.165116f,
0.726260f, -0.000000f, 0.374393f,
0.260810f, -0.000000f, 0.799240f,
0.595148f, 0.045295f, 0.524913f,
0.571821f, -0.000000f, 0.863117f,
0.714903f, -0.000000f, 0.703959f,
-0.110824f, -0.000000f, -0.224247f,
-0.110824f, -0.000000f, 0.518382f,
-0.110824f, 0.045295f, 0.027739f,
0.000000f, 0.075607f, 0.034004f,
-0.110824f, -0.045295f, 0.027739f,
-0.427219f, 0.045295f, -0.322914f,
-0.501040f, -0.000000f, 0.027739f,
-0.427219f, -0.045295f, -0.322914f,
-0.707865f, 0.045295f, -0.493162f,
-1.000000f, -0.000000f, -0.565862f,
-0.737057f, -0.000000f, -0.123207f,
-0.707865f, -0.045295f, -0.493162f,
-0.353372f, -0.000000f, -0.673567f,
-0.912370f, 0.000000f, -0.777113f,
-0.678646f, -0.000000f, -0.863117f,
-0.377206f, -0.045295f, 0.425420f,
-0.377206f, 0.045295f, 0.425420f,
-0.595148f, -0.045295f, 0.524913f,
-0.726260f, -0.000000f, 0.374393f,
-0.619995f, -0.000000f, 0.165116f,
-0.595148f, 0.045295f, 0.524913f,
-0.260810f, -0.000000f, 0.799240f,
-0.714903f, -0.000000f, 0.703959f,
-0.571821f, -0.000000f, 0.863117f,



0.000000f, 0.237737f, -0.146961f,
0.110824f, 0.159651f, -0.224247f,
0.000000f, 0.159651f, -0.409531f,
0.000000f, 0.089350f, 0.452319f,
0.110824f, 0.159651f, 0.518382f,
0.000000f, 0.159651f, 0.726166f,
0.000000f, 0.229472f, 0.452319f,
0.110824f, 0.204945f, 0.027739f,
0.110824f, 0.114356f, 0.027739f,
0.000000f, 0.083911f, 0.034004f,
0.501040f, 0.063330f, 0.027739f,
0.427219f, 0.108598f, -0.322914f,
0.000000f, 0.081565f, -0.146961f,
0.427219f, 0.018035f, -0.322914f,
0.707865f, -0.031338f, -0.493162f,
0.737057f, -0.076606f, -0.123207f,
1.000000f, -0.237737f, -0.565862f,
0.353372f, 0.063330f, -0.673567f,
0.707865f, -0.121901f, -0.493162f,
0.678646f, -0.076606f, -0.863117f,
0.912370f, -0.237737f, -0.777113f,
0.377206f, 0.018035f, 0.425420f,
0.377206f, 0.108598f, 0.425420f,
0.595148f, -0.121901f, 0.524913f,
0.619995f, -0.076606f, 0.165116f,
0.726260f, -0.237737f, 0.374393f,
0.260810f, 0.063330f, 0.799240f,
0.595148f, -0.031338f, 0.524913f,
0.571821f, -0.076606f, 0.863117f,
0.714903f, -0.237737f, 0.703959f,
-0.110824f, 0.159651f, -0.224247f,
-0.110824f, 0.159651f, 0.518382f,
-0.110824f, 0.204945f, 0.027739f,
0.000000f, 0.235257f, 0.034004f,
-0.110824f, 0.114356f, 0.027739f,
-0.427219f, 0.108598f, -0.322914f,
-0.501040f, 0.063330f, 0.027739f,
-0.427219f, 0.018035f, -0.322914f,
-0.707865f, -0.031338f, -0.493162f,
-1.000000f, -0.237737f, -0.565862f,
-0.737057f, -0.076606f, -0.123207f,
-0.707865f, -0.121901f, -0.493162f,
-0.353372f, 0.063330f, -0.673567f,
-0.912370f, -0.237737f, -0.777113f,
-0.678646f, -0.076606f, -0.863117f,
-0.377206f, 0.018035f, 0.425420f,
-0.377206f, 0.108598f, 0.425420f,
-0.595148f, -0.121901f, 0.524913f,
-0.726260f, -0.237737f, 0.374393f,
-0.619995f, -0.076606f, 0.165116f,
-0.595148f, -0.031338f, 0.524913f,
-0.260810f, 0.063330f, 0.799240f,
-0.714903f, -0.237737f, 0.703959f,
-0.571821f, -0.076606f, 0.863117f
};

std::vector<unsigned int> bf_ind =
{
0, 1, 2,
3, 4, 5,
4, 6, 5,
7, 6, 4,
8, 3, 9,
7, 10, 11,
12, 0, 2,
1, 12, 2,
1, 13, 8,
14, 15, 16,
11, 15, 14,
17, 18, 13,
18, 19, 20,
8, 10, 21,
4, 22, 7,
23, 24, 25,
26, 27, 22,
21, 24, 23,
27, 28, 29,
18, 20, 16,
22, 24, 10,
17, 14, 19,
19, 14, 20,
26, 23, 28,
0, 7, 1,
12, 8, 9,
1, 11, 17,
8, 13, 10,
13, 15, 10,
15, 18, 16,
14, 16, 20,
27, 29, 25,
24, 27, 25,
28, 23, 29,
23, 25, 29,
7, 22, 10,
4, 21, 26,
0, 2, 30,
3, 5, 31,
31, 5, 6,
32, 6, 33,
3, 34, 9,
32, 35, 36,
30, 2, 12,
37, 30, 34,
38, 39, 40,
35, 40, 36,
41, 42, 37,
41, 43, 44,
34, 45, 36,
46, 31, 32,
47, 48, 49,
50, 51, 46,
45, 49, 36,
50, 52, 53,
41, 39, 43,
49, 46, 36,
42, 38, 35,
44, 43, 38,
51, 47, 45,
32, 0, 30,
12, 34, 30,
30, 35, 32,
34, 36, 37,
40, 37, 36,
40, 39, 41,
38, 43, 39,
50, 48, 52,
49, 48, 50,
53, 52, 47,
47, 52, 48,
32, 36, 46,
31, 45, 34,
7, 33, 6,
8, 4, 3,
1, 17, 13,
11, 10, 15,
17, 19, 18,
4, 26, 22,
26, 28, 27,
21, 10, 24,
22, 27, 24,
17, 11, 14,
26, 21, 23,
0, 33, 7,
12, 1, 8,
1, 7, 11,
13, 18, 15,
4, 8, 21,
32, 31, 6,
3, 31, 34,
37, 42, 30,
35, 38, 40,
41, 44, 42,
46, 51, 31,
50, 53, 51,
45, 47, 49,
49, 50, 46,
42, 44, 38,
51, 53, 47,
32, 33, 0,
12, 9, 34,
30, 42, 35,
40, 41, 37,
31, 51, 45
};