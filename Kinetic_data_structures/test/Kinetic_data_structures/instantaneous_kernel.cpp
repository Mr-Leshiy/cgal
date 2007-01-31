#define CGAL_CHECK_EXACTNESS
#define CGAL_CHECK_EXPENSIVE

#include <CGAL/Kinetic/basic.h>

#include <CGAL/Kinetic/Exact_simulation_traits.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <algorithm>
#include <iterator>

int main(int, char *[])
{

  typedef CGAL::Kinetic::Exact_simulation_traits Traits;

  Traits tr(0,10000000);  
  CGAL_KINETIC_SET_LOG_LEVEL(CGAL::Kinetic::LOG_LOTS);
 
  std::ifstream in("data/Delaunay_triangulation_2.input");
  if (!in) {
    std::cerr << "Error opening input file: " << "data/Delaunay_triangulation_2.input" << std::endl;
    return EXIT_FAILURE;
  }
  in >> *tr.active_points_2_table_handle();
  {
    CGAL::Delaunay_triangulation_2<Traits::Instantaneous_kernel> del(tr.instantaneous_kernel_object());
    del.geom_traits().set_time(Traits::Instantaneous_kernel::FT(0));
    
    for (Traits::Active_points_2_table::Key_iterator kit= tr.active_points_2_table_handle()->keys_begin();
	 kit !=  tr.active_points_2_table_handle()->keys_end(); ++kit) {
      del.insert(*kit);
    }
    
    del.is_valid(true);
    std::cout << "Triangulation has " << del.number_of_vertices() << " vertices and "
	      << del.number_of_faces() << " faces.\n";
  }

  {
    CGAL::Delaunay_triangulation_2<Traits::Instantaneous_kernel> del(tr.instantaneous_kernel_object());
    del.geom_traits().set_time(Traits::Instantaneous_kernel::Time(0));
    
    for (Traits::Active_points_2_table::Key_iterator kit= tr.active_points_2_table_handle()->keys_begin();
	 kit !=  tr.active_points_2_table_handle()->keys_end(); ++kit) {
      del.insert(*kit);
    }
    
    del.is_valid(true);
    std::cout << "Triangulation has " << del.number_of_vertices() << " vertices and "
	      << del.number_of_faces() << " faces.\n";
  }
  

  return 0;
};
