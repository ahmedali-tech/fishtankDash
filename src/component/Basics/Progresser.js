import React, { useEffect, useState } from "react";
import "./style.css";
import { Line, Circle } from "rc-progress";

const Progresser = ({sensorData}) => {
  // const [percentage, setPercentage] = useState(30);
  if (!sensorData) {
    return null; // or handle this case as per your application's logic
  }
  return (
    <>
      <div className="outer">
        <div style={{ height: 180, width: 180 }}>
          <Circle
            percent={sensorData.value}
            strokeColor="#1e90ff"
            strokeWidth={7}
            trailColor="#F9F5FF"
            trailWidth={7}
            //gapDegree={20}
            //gapPosition='left'
          />
          <div className="info">
            <p style={{color:"#828080"}}>{sensorData.title}</p><br/><p style={{marginTop:1}}>{sensorData.value}</p>
          </div>
        </div>
      </div>
    </>
  );
};

export default Progresser;
