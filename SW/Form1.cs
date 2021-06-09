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
            InitializeComponent();
            _points = new List<PointLatLng>();
            Map.DragButton = MouseButtons.Left;
            Map.MapProvider = GMapProviders.GoogleMap;
            _points.Add(new PointLatLng(33.03581, 31.20008));
            _points.Add(new PointLatLng(33.05087, 31.23065));
            _points.Add(new PointLatLng(33.04864, 31.22344));
            _points.Add(new PointLatLng(33.04492, 31.22087));
            _points.Add(new PointLatLng(33.04879, 31.21932));
            for (int i = 0; i < _points.Count(); i++)
            {
                double lat = _points[i].Lat;
                double lon = _points[i].Lng;
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
