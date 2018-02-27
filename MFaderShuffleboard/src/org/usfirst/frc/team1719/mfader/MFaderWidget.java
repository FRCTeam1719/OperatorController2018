package org.usfirst.frc.team1719.mfader;

import java.io.IOException;
import java.io.OutputStream;

import org.fxmisc.easybind.EasyBind;

import edu.wpi.first.shuffleboard.api.widget.Description;
import edu.wpi.first.shuffleboard.api.widget.ParametrizedController;
import edu.wpi.first.shuffleboard.api.widget.SimpleAnnotatedWidget;
import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

@Description(dataTypes = { Number.class }, name = "MFader")
@ParametrizedController("MFaderWidget.fxml")
public class MFaderWidget extends SimpleAnnotatedWidget<Number> implements ChangeListener<Number> {
    
    private static final String PORT_ID = "COM3";
    private static final int BAUDRATE = 9600;
    private static final int TIMEOUT = 2000;
   
    private CommPortIdentifier port = null;
    private SerialPort serial = null;
    private OutputStream output = null;
    private short pos;
    
    @FXML
    private Pane root;
    @FXML
    private Label numLabel;
    
    @FXML
    private void initialize() {
        numLabel.textProperty().bind(EasyBind.monadic(dataOrDefault).map(Number::toString).orElse("0.0"));
        dataOrDefault.addListener(this);
        try {
            port = CommPortIdentifier.getPortIdentifier(PORT_ID);
            serial = (SerialPort) port.open(getClass().getName(), TIMEOUT);
            serial.setSerialPortParams(BAUDRATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
            output = serial.getOutputStream();
        } catch(NoSuchPortException | PortInUseException | IOException | UnsupportedCommOperationException | NullPointerException ex) {
            ex.printStackTrace();
        }
    }
    
    @Override
    public Pane getView() {
        return root;
    }
    
    @Override
    public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
        pos = newValue.shortValue();
        try {
            /* Hack -- we use the high bit to check byte order,
             * effectively using 7-bit bytes of data.
             * 
             * This does not matter, as we only use 0 to 1024 anyway,
             * so it's 2 bytes either way */
            output.write(pos & 0x7F);
            output.write(((pos>>7) & 0x0F) | 0x80);
            output.flush();
        } catch(IOException ex) {
            ex.printStackTrace();
        };
    }
}
