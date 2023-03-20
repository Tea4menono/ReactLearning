import React from "react";
import ReactDOM from "react-dom/client";
function FancyBorder(props) {
  console.log(props.children);
  return (
    <div className="SplitPane">
      <div className="SplitPane-left">{props.children}</div>
    </div>
  );
}

function WelcomeDialog() {
  return (
    <FancyBorder>
      <div>123111</div>
    </FancyBorder>
  );
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<WelcomeDialog />);
