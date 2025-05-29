import scene.Raster;

cbuffer per_frame_cb
{
    float4 g_colour;
};

VSOut vsMain(VSIn v_in)
{
    return defaultVS(v_in);
}

float4 psMain() : SV_Target
{
    return g_colour;
}