static int convert_color(int color[3])
{
    int     ret_v;

    ret_v = 0;
	printf("%d %d %d\n",color[0], color[1], color[2]);
    ret_v += color[2] % 16;
    ret_v += (color[2] / 16) * 16;
    ret_v += (color[1] % 16) * 32;
    ret_v += (color[1] / 16) * 64;
    ret_v += (color[0] % 16) * 128;
    ret_v += (color[0] / 16) * 256;
    return (ret_v);
}


int main()
{
	int color[3] = {255, 0, 0};
	
	printf("color = %d\n", convert_color(color));
	return (0);
}