function x = pagerank1(U,G,p)

    if nargin < 3, p = .85; end

    % Eliminate any self-referential links
    G = G - diag(diag(G));

    % c = out-degree, r = in-degree
    [n,n] = size(G);
    c = sum(G,1);
    r = sum(G,2);

    % Scale column sums to be 1 (or 0 where there are no out links).
    k = find(c~=0);
    D = sparse(k,k,1./c(k),n,n);

    % Solve (I - p*G*D)*x = e
    e = ones(n,1);
    I = speye(n,n);
    x = (I - p*G*D)\e;

    % Normalize so that sum(x) == 1.
    x = x/sum(x);

end
