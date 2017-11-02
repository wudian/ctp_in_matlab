% compute the position sizing based on ratio of the pair contract value.
%{
Illustration,
contract1's value = price * multipier
contract2's value = price * mulpipier
Thus, pair ratio = contract1's value / contract2's value
min. position size is 1.

The column size of parameter "Prices" and "Multipliers" must be 2 column 
due to pair trading.
%}

function [oPosSizes] = valueRatioPositionSizing(ePrices, eMulitpliers , eWeight , betaPositionSize)

ePrices = ePrices(:)';
eWeight = eWeight(:)';

if betaPositionSize
    aBaseValues = ePrices .* abs(eWeight);
else
    aBaseValues = ePrices .* eMulitpliers;
end

%-- scale to the first position size
oPosSizes = aBaseValues ./ aBaseValues(1);

%-- round to the nearest 1/100 of a contract.
oPosSizes = round(oPosSizes * 10) ./ 10;

end

