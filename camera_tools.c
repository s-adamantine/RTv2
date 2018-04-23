#include "rtv1.h"

t_cam	*get_selected_cam(t_scene *scene, int id)
{
	t_list	*tmp_cam;
	t_cam	*cam;
	static int	a = 0;

	a++;
	if (id >= scene->cam_set)
		return (NULL);
	tmp_cam = scene->cameras;
	while (tmp_cam && tmp_cam->content)
	{
		cam = (t_cam *)tmp_cam->content;
		if (cam->id == id)
			return (cam);
		tmp_cam = tmp_cam->next;
	}
	return (NULL);
}
