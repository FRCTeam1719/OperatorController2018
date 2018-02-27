package org.usfirst.frc.team1719.mfader;

import java.util.List;

import com.google.common.collect.ImmutableList;

import edu.wpi.first.shuffleboard.api.plugin.Description;
import edu.wpi.first.shuffleboard.api.plugin.Plugin;
import edu.wpi.first.shuffleboard.api.widget.ComponentType;
import edu.wpi.first.shuffleboard.api.widget.WidgetType;

@Description(group="frc1719",name="MFader",version="0.0.1",summary="Allows for controlling of a motorized fader through an Arduino Leonardo")
public class MFaderPlugin extends Plugin {
    @Override
    public @SuppressWarnings("rawtypes")List<ComponentType> getComponents() {
        return ImmutableList.of(WidgetType.forAnnotatedWidget(MFaderWidget.class));
    }
}
