<GameProjectFile>
  <PropertyGroup Type="Layer" Name="GamePlayUI" ID="76264361-bb85-4b5b-a36f-dbafb750e4e6" Version="2.0.6.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" FrameEvent="" Tag="21" ctype="LayerObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="720.0000" Y="1280.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="topBar" ActionTag="-697093686" FrameEvent="" Tag="101" ObjectIndex="1" IconVisible="True" ctype="SingleNodeObjectData">
            <Position X="360.0000" Y="1224.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="0.0000" Y="0.0000" />
            <PrePosition X="0.5000" Y="0.9563" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="propSprite" ActionTag="-1544788414" FrameEvent="" Tag="39" ObjectIndex="2" ctype="SpriteObjectData">
                <Position X="0.0000" Y="0.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="72.0000" Y="53.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="FlyBoot.png" />
              </NodeObjectData>
              <NodeObjectData Name="score" ActionTag="-1772200976" FrameEvent="" Tag="7" ObjectIndex="1" ctype="SpriteObjectData">
                <Position X="0.0001" Y="-3.9999" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="720.0000" Y="113.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ScoreBackground.png" />
              </NodeObjectData>
              <NodeObjectData Name="coinAmountLabel" ActionTag="-174313221" FrameEvent="" Tag="11" ObjectIndex="1" FontSize="30" LabelText="9999" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                <Position X="-283.0015" Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="80.0000" Y="42.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="Arial Black.ttf" />
              </NodeObjectData>
              <NodeObjectData Name="distanceLabel" ActionTag="-839900757" FrameEvent="" Tag="14" ObjectIndex="3" FontSize="30" LabelText="9999" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                <Position X="251.9927" Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="80.0000" Y="42.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="Arial Black.ttf" />
              </NodeObjectData>
            </Children>
          </NodeObjectData>
          <NodeObjectData Name="bottomBar" ActionTag="-1071883325" FrameEvent="" Tag="199" ObjectIndex="2" IconVisible="True" ctype="SingleNodeObjectData">
            <Position X="360.0002" Y="50.0001" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="0.0000" Y="0.0000" />
            <PrePosition X="0.5000" Y="0.0391" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="heartLabel" ActionTag="-1551018922" FrameEvent="" Tag="12" ObjectIndex="2" FontSize="30" LabelText="9999" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
                <Position X="-30.0001" Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="80.0000" Y="42.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="Arial Black.ttf" />
              </NodeObjectData>
              <NodeObjectData Name="Heart" ActionTag="-2084880983" FrameEvent="" Tag="13" ObjectIndex="3" ctype="SpriteObjectData">
                <Position X="-77.0000" Y="0.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="76.0000" Y="106.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Heart.png" />
              </NodeObjectData>
              <NodeObjectData Name="pauseButton" ActionTag="-1154167396" FrameEvent="" Tag="8" ObjectIndex="1" TouchEnable="True" FontSize="14" ButtonText="" Scale9Width="131" Scale9Height="77" ctype="ButtonObjectData">
                <Position X="292.0078" Y="0.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="131.0000" Y="77.0000" />
                <PrePosition X="0.0000" Y="0.0000" />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" />
                <NormalFileData Type="Normal" Path="Pause.png" />
              </NodeObjectData>
            </Children>
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>