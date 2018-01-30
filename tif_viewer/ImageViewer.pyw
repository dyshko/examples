import wx

class ImageViewer(wx.Frame):
    """ class ImageViewer creates an image viewer, preserving aspect ratio of the image """
    
    def __init__(self):
        #create frame
        wx.Frame.__init__(self, None, wx.ID_ANY, style=wx.DEFAULT_FRAME_STYLE^(wx.MAXIMIZE_BOX))
        self.SetTitle('Image Viewer')

        #set minimum size of the window
        self.SetSizeHints(200, 200)

        #disable logging (to suppress non-python exeptions)
        wx.Log.EnableLogging(False)

        #add image handlers (includding tif)
        wx.InitAllImageHandlers()

        #resize listener
        self.Bind(wx.EVT_SIZE, self.OnSizeChanged)

        #add locale to suppress locale warnings
        self.locale = wx.Locale(wx.LANGUAGE_ENGLISH)

        #the wx.Image object (to be read from file)
        self.img = None

        #the wx.Bitmap object (to be transformed and scaled from the source image)
        self.scaled_bitmap = None

        #create panel that will display the scaled bitmap
        self.panel = wx.Panel(self, wx.ID_ANY)
        #self.panel.SetBackgroundColour(wx.WHITE)

        #create menubar
        menuBar = wx.MenuBar()
        fileMenu = wx.Menu()
        open_menu_item = fileMenu.Append(wx.NewId(), "Open",
                                       "Open the image")
        menuBar.Append(fileMenu, "&File")
        self.Bind(wx.EVT_MENU, self.OnFileSelect, open_menu_item)
        self.SetMenuBar(menuBar)

    def ErrorMessage(self, text):
        """Pops up an error with text"""
        dlg = wx.MessageDialog(self, text , "Error")
        dlg.ShowModal()
        
    def ReadImage(self, image_pathname):
        """ read the image from file """
        if wx.Image.CanRead(image_pathname):
            raw_image = wx.Image(image_pathname, wx.BITMAP_TYPE_ANY)
            if raw_image.IsOk():            
                #set new current image only if everything is Ok
                self.img = raw_image

                #clear alpha to avoid transparency issues
                if self.img.HasAlpha():
                    self.img.ClearAlpha()
            else:
                self.ErrorMessage("Bad or corrupted image!")
        else:
            self.ErrorMessage("Bad path or image name!")
        self.ResizeImage()
                

    def ResizeImage(self):
        """resize the displayed bitmap preserving the aspect ratio"""
        if self.img is None:
            return

        #get dimensions of the panel (canvas)
        canvas_width, canvas_height = self.panel.GetSize()

        #nonzero dimensions are asserted while the image is read from file
        image_width, image_height = self.img.GetSize()
        
        aspect_ratio = image_width/image_height

        #new scaled dimensions with aspect ratio preserved
        width = int(min( canvas_width, canvas_height*aspect_ratio))
        height = int(width / aspect_ratio)

        #destroy old bitmap and add new bitmap to the panel
        #note that the original image is unchanged and only its temporary copy is rescaled
        #otherwise, the quality of the image would be affected with each rescaling
        if not self.scaled_bitmap is None:
            self.scaled_bitmap.Destroy()
        
        img_copy = wx.Image(self.img)
            
        img_rescaled = img_copy.Rescale(width, height)

        if not img_rescaled is None:
            self.scaled_bitmap = wx.StaticBitmap(self.panel, wx.ID_ANY,
                                             img_rescaled.ConvertToBitmap(), size = (width, height), pos = (0,0))


    def OnFileSelect(self, event):
        """select the image file"""
        with wx.FileDialog(self, "Open image file", wildcard="TIF files (*.tif)|*.tif;*.tiff") as fileDialog:

            if fileDialog.ShowModal() == wx.ID_CANCEL:
                return     # do nothing if no file is selected

            pathname = fileDialog.GetPath()
            self.ReadImage(pathname)
        event.Skip()
            
            
    def OnSizeChanged(self, event):
        """hangle size change event"""
        self.ResizeImage()
        self.Refresh()
        event.Skip()

app = wx.App()      # Create the app
ImageViewer().Show() # Show the frame
app.MainLoop()
