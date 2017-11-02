function out = getContractSpecification(contractName , mktInfo)

allNames = {mktInfo.market.symbol};
indx = strncmp(contractName , allNames , length(contractName));
out = mktInfo.market(indx);
