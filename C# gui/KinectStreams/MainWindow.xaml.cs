using Microsoft.Kinect;
using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace KinectStreams
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Members

        Mode _mode = Mode.Color;

        KinectSensor _sensor;
        MultiSourceFrameReader _reader;
        int index = 0;

        byte[] videodata = new byte[1920*1080* ((PixelFormats.Bgr32.BitsPerPixel + 7) / 8) * 65];

        #endregion

        #region Constructor

        public MainWindow()
        {
            InitializeComponent();
        }

        #endregion

        #region Event handlers

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _sensor = KinectSensor.GetDefault();

            if (_sensor != null)
            {
                _sensor.Open();

                _reader = _sensor.OpenMultiSourceFrameReader(FrameSourceTypes.Color);
                _reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if (_reader != null)
            {
                _reader.Dispose();
            }

            if (_sensor != null)
            {
                _sensor.Close();
            }
        }

        void Reader_MultiSourceFrameArrived(object sender, MultiSourceFrameArrivedEventArgs e)
        {
            var reference = e.FrameReference.AcquireFrame();

            // Color
            using (var frame = reference.ColorFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    index++;
                    int width = frame.FrameDescription.Width;
                    int height = frame.FrameDescription.Height;
                    PixelFormat format = PixelFormats.Bgr32;
                    byte[] last = new byte[width * height * ((format.BitsPerPixel + 7) / 8)];
                    byte[] pixels = new byte[width * height * ((format.BitsPerPixel + 7) / 8)];
                    pixels.CopyTo(last, 0);
                    if (frame.RawColorImageFormat == ColorImageFormat.Bgra)
                    {
                        frame.CopyRawFrameDataToArray(pixels);
                    }
                    else
                    {
                        frame.CopyConvertedFrameDataToArray(pixels, ColorImageFormat.Bgra);
                    }
                    //Console.WriteLine(frame.RelativeTime);
                    if (_mode == Mode.HighPass) {
                        //camera.Source = frame.ToBitmap();
                        for (int i = 0; i < pixels.Length;)
                        {
                            if (pixels[i] < 253) pixels[i] = 0;
                            if (pixels[i + 1] < 253) pixels[i + 1] = 0;
                            if (pixels[i + 2] < 253) pixels[i + 2] = 0;
                            //Console.WriteLine("B:{0} G:{1} R:{2} A:{3}", pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
                            i += 4;
                        }
                    }
                    else if (_mode == Mode.LowPass)
                    {
                        //pixels.CopyTo(videodata, index);
                        for (int i = 0; i < pixels.Length;)
                        {
                            if(pixels[i] + pixels[i + 1] + pixels[i+2] > last[i] + last[i+1] + last[i + 2])
                            {
                                pixels[i] = 255;
                                pixels[i + 1] = 255;
                                pixels[i + 2] = 255;
                            }
                            else
                            {
                                pixels[i] = 0;
                                pixels[i + 1] = 0;
                                pixels[i + 2] = 0;
                            }
                            //Console.WriteLine("B:{0} G:{1} R:{2} A:{3}", pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
                            i += 4;
                        }

                    }
                    int stride = width * format.BitsPerPixel / 8;
                    ImageSource res = BitmapSource.Create(width, height, 96, 96, format, null, pixels, stride);
                    camera.Source = res;
                }
            }
        }

        private void Color_Click(object sender, RoutedEventArgs e)
        {
            _mode = Mode.Color;
        }

        private void High_Pass_click(object sender, RoutedEventArgs e)
        {
            _mode = Mode.HighPass;
        }

        private void Low_Pass_click(object sender, RoutedEventArgs e)
        {
            _mode = Mode.LowPass;
        }

        #endregion
    }

    public enum Mode
    {
        Color,
        HighPass,
        LowPass
    }
}
