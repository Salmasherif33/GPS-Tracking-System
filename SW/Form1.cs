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
        }

        private void gMapControl1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
           // GMapProviders.GoogleMap.ApiKey =AppConfig.
            Map.DragButton = MouseButtons.Left;
            Map.MapProvider = GMapProviders.GoogleMap;
            double lat = Convert.ToDouble(txtLat.Text);
            double lon = Convert.ToDouble(txtLong.Text);
            Map.Position = new PointLatLng(lat, lon);
            Map.MinZoom = 1;
            Map.MaxZoom = 100;
            Map.Zoom = 10;//zoom level


            PointLatLng point = new PointLatLng(lat ,lon);
            GMapMarker marker = new GMarkerGoogle(point, GMarkerGoogleType.red_small);
            //1.creat ovelay
            GMapOverlay markers = new GMapOverlay("markers");
            //2.add all available markers to overlay
            markers.Markers.Add(marker);
            //3.cover maps with ovelay
            Map.Overlays.Add(markers);


        }

        private void btnAddPoint_Click(object sender, EventArgs e)
        {
            _points.Add(new PointLatLng(Convert.ToDouble(txtLat.Text), Convert.ToDouble(txtLong.Text)));
        }

        private void btnClearlist_Click(object sender, EventArgs e)
        {
            _points.Clear();
        }

        private void btnGetRouteinfo_Click(object sender, EventArgs e)
        {
            var route = GoogleMapProvider.Instance.GetRoute(_points[0], _points[1], false, false, 14);
            //for refrance
            var r = new GMapRoute(route.Points,"My Route")
            {
                Stroke = new Pen(Color.Red, 5)
            };
            //to add to my map
            var routes = new GMapOverlay("routes");
            //to add r to routes
            routes.Routes.Add(r);
            //add to map
            Map.Overlays.Add(routes);
        }
    }
}
