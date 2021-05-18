% Fredrik Tåkvist
% ---------------
% move the elevator to indicated position
function move_lift(pos)
    global floorPos liftLH liftRH liftDH
    yoffs = floorPos(4) * (pos - 1);
    liftLH.Position(2) = floorPos(2) + yoffs;
    liftRH.Position(2) = floorPos(2) + yoffs;
    liftDH.Position(2) = floorPos(2) + yoffs;
end

