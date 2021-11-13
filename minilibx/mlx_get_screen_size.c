int mlx_get_screen_size(t_win *win, int *sizex, int *sizey)
{
	printf("mlx\n");
	CGRect mainMonitor = CGDisplayBounds(CGMainDisplayID());
	CGFloat monitorHeight = CGRectGetHeight(mainMonitor);
	CGFloat monitorWidth = CGRectGetWidth(mainMonitor);
	*sizey = monitorHeight;
	*sizex = monitorWidth;
	return (0);
}
