using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsForms;
using GMap.NET.WindowsForms.Markers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace map
{
    public partial class Form1 : Form
    {
        private List<PointLatLng> _points;
        public Form1()
        {
            string text = System.IO.File.ReadAllText(@"E:\3rd_computer2\Microprocessor\Project\examp.txt");
            string[] lines = System.IO.File.ReadAllLines(@"E:\3rd_computer2\Microprocessor\Project\examp.txt");

            InitializeComponent();
            _points = new List<PointLatLng>();
            Map.DragButton = MouseButtons.Left;
            Map.MapProvider = GMapProviders.GoogleMap;
            
            for (int i = 0; i < 4; i=i+2)
            {
                double lat = Convert.ToDouble(lines[i]);
                double lon = Convert.ToDouble(lines[i+1]);
                _points.Add(new PointLatLng(lat, lon));

                Map.Position = new PointLatLng(lat, lon);
                Map.MinZoom = 1;
                Map.MaxZoom = 100;
                Map.Zoom = 10;//zoom level
                PointLatLng point = new PointLatLng(lat, lon);
                GMapMarker marker = new GMarkerGoogle(point, GMarkerGoogleType.red_small);
                //1.creat ovelay
                GMapOverlay markers = new GMapOverlay("markers");
                //2.add all available markers to overlay
                markers.Markers.Add(marker);
                //3.cover maps with ovelay
                Map.Overlays.Add(markers);
            }

        }

        private void gMapControl1_Load(object sender, EventArgs e)
        {

        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
